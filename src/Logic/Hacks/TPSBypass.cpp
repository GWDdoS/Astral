#include "../../includes.hpp"
#include "../../builds/assembler.hpp"

constexpr float MIN_TPS = 0.f;

namespace Astral::Hacks::Global {
    
    // Platform-specific tick type
    using TicksType =
        #ifdef GEODE_IS_WINDOWS
        uint32_t
        #elif defined(GEODE_IS_ANDROID64)
        uint32_t
        #elif defined(GEODE_IS_ANDROID32)
        float
        #else
        float
        #endif
        ;

    static TicksType g_expectedTicks = 0;
    
    TicksType& expectedTicks() { return g_expectedTicks; }

    class TPSBypass {
    private:
        geode::Patch* m_mainPatch = nullptr;
        
        static void forceDisable() {
            tpsEnabled = false;
            // Add safeguard to prevent re-enabling if something goes wrong
        }

        bool setupPatches() {
            auto base = reinterpret_cast<uint8_t*>(geode::base::get());
            auto baseSize = geode::Mod::get()->getMetadata().getBinarySize();

            intptr_t addr = -1;
            std::vector<uint8_t> bytes;

            #ifdef GEODE_IS_WINDOWS
            {
                using namespace Astral::Assembler::x86_64;
                // Pattern to find in GJBaseGameLayer::update
                // This is where the game calculates expected ticks
                addr = /* Find pattern in memory - you'll need to use a pattern scanner */;
                
                if (addr != -1) {
                    bytes = Builder(addr)
                        .movabs(Register64::rax, std::bit_cast<uint64_t>(&g_expectedTicks))
                        .mov(Register32::r11d, Register64::rax)
                        .jmp(addr + 0x43, true)
                        .nop(4)
                        .build();
                }
            }
            #elif defined(GEODE_IS_ANDROID64)
            {
                using namespace Astral::Assembler::arm64;
                // Find the update function
                auto func = dlsym(RTLD_DEFAULT, "_ZN15GJBaseGameLayer6updateEf");
                // Pattern search within the function
                // addr = pattern_search(func, pattern);
                
                if (addr != -1) {
                    bytes = Builder(addr)
                        .mov(Register::x9, std::bit_cast<uint64_t>(&g_expectedTicks))
                        .ldr(Register::w0, Register::x9)
                        .b(addr + 0x2c, true)
                        .build();
                }
            }
            #elif defined(GEODE_IS_ANDROID32)
            {
                using namespace Astral::Assembler::armv7;
                auto func = dlsym(RTLD_DEFAULT, "_ZN15GJBaseGameLayer6updateEf");
                // Pattern search
                
                if (addr != -1) {
                    bytes = Builder(addr)
                        .mov(Register::r1, std::bit_cast<uint32_t>(&g_expectedTicks))
                        .ldr_t(Register::r0, Register::r1)
                        .nop_t()
                        .build();
                }
            }
            #endif

            if (addr == -1 || bytes.empty()) {
                geode::log::error("TPS Bypass: Failed to find patch address");
                return false;
            }

            auto patchRes = geode::Mod::get()->patch(reinterpret_cast<void*>(addr + base), bytes);
            if (!patchRes) {
                geode::log::error("TPS Bypass: Failed to apply patch: {}", patchRes.unwrapErr());
                return false;
            }

            m_mainPatch = patchRes.unwrap();
            geode::log::info("TPS Bypass: Patch applied at offset 0x{:X}", addr);
            
            // Start disabled
            m_mainPatch->disable();
            return true;
        }

    public:
        void init() {
            if (!setupPatches()) {
                forceDisable();
                return;
            }

            // Setup callbacks for enabling/disabling
            // You'll need to implement your config system's callback mechanism
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
            float frameTime = 1.f / tpsValue;
            director->setAnimationInterval(frameTime);
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

            // Handle resume timer
            if (m_resumeTimer > 0) {
                m_resumeTimer--;
                return 0.0f;
            }

            auto fields = m_fields.self();
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
        void updateProgressbar() {
            auto timestamp = m_level->m_timestamp;
            auto currentProgress = m_gameState.m_currentProgress;

            // Fix percentage calculation for non-240 TPS
            if (timestamp > 0 && tpsValue != 240.f && tpsEnabled) {
                // Recalculate based on actual time passed
                auto actualTime = m_gameState.m_levelTime;
                auto progress = (actualTime / (timestamp / 240.f)) * 100.f;
                m_gameState.m_currentProgress = timestamp * progress / 100.f;
            }

            PlayLayer::updateProgressbar();
            m_gameState.m_currentProgress = currentProgress;
        }

        void destroyPlayer(PlayerObject* player, GameObject* object) override {
            auto timestamp = m_level->m_timestamp;
            auto currentProgress = m_gameState.m_currentProgress;

            if (timestamp > 0 && tpsValue != 240.f && tpsEnabled) {
                auto actualTime = m_gameState.m_levelTime;
                auto progress = (actualTime / (timestamp / 240.f)) * 100.f;
                m_gameState.m_currentProgress = timestamp * progress / 100.f;
            }

            PlayLayer::destroyPlayer(player, object);
            m_gameState.m_currentProgress = currentProgress;
        }

        void levelComplete() {
            auto oldTimestamp = m_gameState.m_unkUint2;
            
            // Store timestamp as if it was 240 TPS
            if (tpsValue != 240.f && tpsEnabled) {
                auto ticks = static_cast<uint32_t>(std::round(m_gameState.m_levelTime * 240));
                m_gameState.m_unkUint2 = ticks;
            }
            
            PlayLayer::levelComplete();
            m_gameState.m_unkUint2 = oldTimestamp;
        }
    };

    // Initialization function to be called from your main initialization
    void initTPSBypass() {
        if (!s_tpsBypass) {
            s_tpsBypass = new TPSBypass();
            s_tpsBypass->init();
        }
    }

    // Update function to sync FPS with TPS when value changes
    void updateTPSBypass() {
        if (s_tpsBypass) {
            s_tpsBypass->updateState();
            
            // Sync FPS with TPS if enabled
            if (tpsEnabled) {
                TPSBypass::syncFPSWithTPS(tpsValue);
            } else {
                // Reset to default 60 FPS
                TPSBypass::syncFPSWithTPS(60.f);
            }
        }
    }
}