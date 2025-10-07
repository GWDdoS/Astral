#include "../../includes.hpp"
#include "../../builds/assembler.hpp"
#include <bit>

#ifdef GEODE_IS_ANDROID
#include <dlfcn.h>
#endif

constexpr float MIN_TPS = 0.f;

namespace Astral::Hacks::Global {
    
    // Configuration variables (you'll need to connect these to your config system)
    static bool tpsEnabled = true;

    
    // Platform-specific tick type
    using TicksType =
        #if defined(GEODE_IS_WINDOWS) || defined(GEODE_IS_ANDROID64)
        uint32_t
        #else
        float  // Android32, iOS, macOS
        #endif
        ;

    static TicksType g_expectedTicks = 0;
    
    TicksType& expectedTicks() { return g_expectedTicks; }

    class TPSBypass {
    private:
        geode::Patch* m_mainPatch = nullptr;
        
        static void forceDisable() {
            tpsEnabled = false;
        }

        // Improved pattern matching helper
        static intptr_t findPattern(const uint8_t* data, size_t dataSize, const char* pattern) {
            std::vector<int> patternBytes;
            std::vector<bool> mask;
            
            // Parse pattern (e.g., "FF 90 ? ? ? ? F3 0F 10")
            std::istringstream iss(pattern);
            std::string byte;
            while (iss >> byte) {
                if (byte == "^") continue; // Skip position marker, but don't add to pattern
                if (byte == "?") {
                    patternBytes.push_back(0);
                    mask.push_back(false);
                } else {
                    try {
                        patternBytes.push_back(std::stoi(byte, nullptr, 16));
                        mask.push_back(true);
                    } catch (...) {
                        geode::log::error("Invalid pattern byte: {}", byte);
                        return -1;
                    }
                }
            }
            
            if (patternBytes.empty()) return -1;
            
            // Search for pattern
            for (size_t i = 0; i <= dataSize - patternBytes.size(); i++) {
                bool found = true;
                for (size_t j = 0; j < patternBytes.size(); j++) {
                    if (mask[j] && data[i + j] != static_cast<uint8_t>(patternBytes[j])) {
                        found = false;
                        break;
                    }
                }
                if (found) return static_cast<intptr_t>(i);
            }
            
            return -1;
        }

        bool setupPatches() {
            auto base = reinterpret_cast<uintptr_t>(geode::base::get());
            auto basePtr = reinterpret_cast<uint8_t*>(base);
            // Use a reasonable size to search
            size_t baseSize = 0x10000000; // 256MB

            intptr_t offset = -1;
            std::vector<uint8_t> bytes;

            #ifdef GEODE_IS_WINDOWS
            {
                using namespace Astral::Assembler::x86_64;
                // 2.2074: 0x232294
                // Pattern: FF 90 ? ? ? ? F3 0F 10 8E
                offset = findPattern(basePtr, baseSize, "FF 90 ? ? ? ? F3 0F 10 8E");
                
                if (offset != -1) {
                    uintptr_t addr = base + offset;
                    bytes = Builder(addr)
                        .movabs(Register64::rax, std::bit_cast<uint64_t>(&g_expectedTicks))
                        .mov(Register32::r11d, Register64::rax)
                        .jmp(static_cast<int32_t>(addr + 0x43), true)
                        .nop(4)
                        .build();
                }
            }
            #elif defined(GEODE_IS_IOS) || defined(GEODE_IS_ARM_MAC)
            {
                using namespace Astral::Assembler::arm64;
                // 2.2074: 0x200C30 (iOS) / 0x119454 (macOS)
                // Pattern: 00 19 20 1E 02 10 22 1E
                offset = findPattern(basePtr, baseSize, "00 19 20 1E 02 10 22 1E");
                
                if (offset != -1) {
                    uintptr_t addr = base + offset;
                    bytes = Builder(addr)
                        .mov(Register::x9, std::bit_cast<uint64_t>(&g_expectedTicks))
                        .ldr(FloatRegister::s0, Register::x9)
                        .nop(5) // 20 bytes = 5 instructions
                        .build();
                }
            }
            #elif defined(GEODE_IS_INTEL_MAC)
            {
                using namespace Astral::Assembler::x86_64;
                // 2.2074: 0x14233E
                // Pattern: 0F 28 C5 F3 0F 5D 83
                offset = findPattern(basePtr, baseSize, "0F 28 C5 F3 0F 5D 83");
                
                if (offset != -1) {
                    uintptr_t addr = base + offset;
                    bytes = Builder(addr)
                        .movabs(Register64::rax, std::bit_cast<uint64_t>(&g_expectedTicks))
                        .movss(XmmRegister::xmm0, Register64::rax)
                        .jmp(static_cast<int32_t>(addr + 0x36), true)
                        .nop(3)
                        .build();
                }
            }
            #elif defined(GEODE_IS_ANDROID64)
            {
                using namespace Astral::Assembler::arm64;
                // 2.2074: 0x87DA40 (google) / 0x87BE28 (amazon)
                // Pattern: 0B 19 2B 1E 0F 10 62 1E 00 10 2E 1E
                auto func = dlsym(RTLD_DEFAULT, "_ZN15GJBaseGameLayer6updateEf");
                if (func) {
                    auto funcPtr = static_cast<const uint8_t*>(func);
                    offset = findPattern(funcPtr, 0x500, "0B 19 2B 1E 0F 10 62 1E 00 10 2E 1E");
                    
                    if (offset != -1) {
                        uintptr_t addr = reinterpret_cast<uintptr_t>(funcPtr) + offset;
                        bytes = Builder(addr)
                            .mov(Register::x9, std::bit_cast<uint64_t>(&g_expectedTicks))
                            .ldr(Register::w0, Register::x9)
                            .b(static_cast<int32_t>(addr + 0x2c), true)
                            .build();
                        
                        // Adjust offset for patching
                        offset = addr - base;
                    }
                }
            }
            #elif defined(GEODE_IS_ANDROID32)
            {
                using namespace Astral::Assembler::armv7;
                // 2.2074: 0x4841BC (google) / 0x483F0C (amazon)
                // Pattern: B7 EE C7 7A 27 EE 06 7B F7 EE C7 7B 17 EE 90 0A
                auto func = dlsym(RTLD_DEFAULT, "_ZN15GJBaseGameLayer6updateEf");
                if (func) {
                    auto funcPtr = static_cast<const uint8_t*>(func);
                    offset = findPattern(funcPtr, 0x500, "B7 EE C7 7A 27 EE 06 7B F7 EE C7 7B 17 EE 90 0A");
                    
                    if (offset != -1) {
                        uintptr_t addr = reinterpret_cast<uintptr_t>(funcPtr) + offset;
                        bytes = Builder(addr)
                            .mov(Register::r1, std::bit_cast<uint32_t>(&g_expectedTicks))
                            .ldr_t(Register::r0, Register::r1)
                            .nop_t()
                            .build();
                        
                        // Adjust offset for patching
                        offset = addr - base;
                    }
                }
            }
            #endif

            if (offset == -1 || bytes.empty()) {
                geode::log::error("TPS Bypass: Failed to find patch address");
                return false;
            }

            // Apply patch using absolute address
            auto patchAddr = reinterpret_cast<void*>(base + offset);
            auto patchRes = geode::Mod::get()->patch(patchAddr, bytes);
            if (!patchRes) {
                geode::log::error("TPS Bypass: Failed to apply patch: {}", patchRes.unwrapErr());
                return false;
            }

            m_mainPatch = patchRes.unwrap();
            geode::log::info("TPS Bypass: Patch applied at offset 0x{:X}", offset);
            
            // Start disabled
            if (m_mainPatch) {
                m_mainPatch->disable();
            }
            return true;
        }

    public:
        void init() {
            if (!setupPatches()) {
                forceDisable();
                return;
            }
        }

        void updateState() {
            if (!m_mainPatch) return;

            if (tpsEnabled) {
                m_mainPatch->enable();
            } else {
                m_mainPatch->disable();
            }
        }

        static void syncFPSWithTPS(float tpsValue) {
            auto* director = cocos2d::CCDirector::sharedDirector();
            if (director && tpsValue > 0.f) {
                float frameTime = 1.f / tpsValue;
                director->setAnimationInterval(frameTime);
            }
        }
    };

    // Singleton instance
    static TPSBypass* s_tpsBypass = nullptr;

    class $modify(TPSBypassGJBGLHook, GJBaseGameLayer) {
        struct Fields {
            double m_extraDelta = 0.0;
        };

        void update(float dt) override {
            if (!tpsEnabled || tpsValue == 240.f || !PlayLayer::get()) {
                return GJBaseGameLayer::update(dt);
            }

            auto fields = m_fields.self();
            
            // Handle framestep mode
            if (framestepEnabled) {
                expectedTicks() = 1;
                return GJBaseGameLayer::update(1.f / tpsValue);
            }

            // Handle resume timer
            if (m_resumeTimer > 0) {
                --m_resumeTimer;
                dt = 0.f;
            }

            // Accumulate delta time
            fields->m_extraDelta += dt;

            // Calculate timestep
            auto timeWarp = std::min(m_gameState.m_timeWarp, 1.f);
            auto newTPS = tpsValue / timeWarp;
            auto spt = 1.0 / newTPS;

            // Calculate number of steps
            auto steps = std::round(fields->m_extraDelta / spt);
            auto totalDelta = steps * spt;
            
            // Update remaining delta
            fields->m_extraDelta -= totalDelta;
            
            // Set expected ticks for the patch
            expectedTicks() = static_cast<TicksType>(steps);

            // Call original update with calculated delta
            GJBaseGameLayer::update(static_cast<float>(totalDelta));
        }

        float getModifiedDelta(float dt) {
            if (!tpsEnabled || tpsValue == 240.f || !PlayLayer::get()) {
                return GJBaseGameLayer::getModifiedDelta(dt);
            }

            auto fields = m_fields.self();
            
            // Handle resume timer
            if (m_resumeTimer > 0) {
                --m_resumeTimer;
                return 0.0f;
            }

            auto timeWarp = std::min(m_gameState.m_timeWarp, 1.f);
            auto spt = 1.f / tpsValue;
            
            // Calculate adjusted delta
            auto totalDelta = dt + fields->m_extraDelta;
            auto timestep = timeWarp * spt;
            auto steps = std::round(totalDelta / timestep);
            auto newDelta = steps * timestep;
            
            // Store extra delta for next frame
            fields->m_extraDelta = totalDelta - newDelta;
            
            return static_cast<float>(newDelta);
        }
    };

    class $modify(TPSBypassPLHook, PlayLayer) {
        int calculationFix() {
            auto timestamp = m_level->m_timestamp;
            auto currentProgress = m_gameState.m_currentProgress;
            
            // Fix percentage calculation for non-240 TPS
            if (timestamp > 0 && tpsValue != 240.f) {
                // Recalculate based on actual time passed
                auto actualTime = m_gameState.m_levelTime;
                auto progress = (actualTime / (timestamp / 240.f)) * 100.f;
                m_gameState.m_currentProgress = timestamp * progress / 100.f;
            }
            
            return currentProgress;
        }

        void updateProgressbar() {
            auto currentProgress = calculationFix();
            PlayLayer::updateProgressbar();
            m_gameState.m_currentProgress = currentProgress;
        }

        void destroyPlayer(PlayerObject* player, GameObject* object) override {
            auto currentProgress = calculationFix();
            PlayLayer::destroyPlayer(player, object);
            m_gameState.m_currentProgress = currentProgress;
        }

        void levelComplete() {
            auto oldTimestamp = m_gameState.m_unkUint2;
            
            // Store timestamp as if it was 240 TPS
            if (tpsValue != 240.f) {
                auto ticks = static_cast<uint32_t>(std::round(m_gameState.m_levelTime * 240));
                m_gameState.m_unkUint2 = ticks;
            }
            
            PlayLayer::levelComplete();
            m_gameState.m_unkUint2 = oldTimestamp;
        }
    };

    // Public API functions
    void initTPSBypass() {
        if (!s_tpsBypass) {
            s_tpsBypass = new TPSBypass();
            s_tpsBypass->init();
        }
    }

    void updateTPSBypass() {
        if (s_tpsBypass) {
            s_tpsBypass->updateState();
            TPSBypass::syncFPSWithTPS(240.0f);
            
        }
    }

    // Setters for configuration (connect these to your config system)
    void setTPSEnabled(bool enabled) {
        tpsEnabled = enabled;
        updateTPSBypass();
    }

    void setTPSValue(float value) {
        tpsValue = value;
        updateTPSBypass();
    }

    void setFramestepEnabled(bool enabled) {
        framestepEnabled = enabled;
    }
}