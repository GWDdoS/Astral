#include "../../includes.hpp"
#include <../../builds/assembler.hpp>
#include <sinaps.hpp> // idk its in eclipse, lets just see for now
/* Also need to implement fps to keep speed the same
namespace Astral::Hacks::Global {
    
    // Find what vars the platform uses. Funny they all different, i wouldnt have known.
    using TicksType =
        GEODE_WINDOWS(uint32_t)
        GEODE_ANDROID64(uint32_t)
        GEODE_ANDROID32(float)
        GEODE_IOS(float)
        GEODE_ARM_MAC(float)
        GEODE_INTEL_MAC(float);
    static TicksType g_expectedTicks = 0;
    
    // apparently this gets the ticks
    TicksType& expectedTicks() { 
        return g_expectedTicks; 
    }

    class TPSBypassWithPatches {
    private:
        geode::Patch* m_patch = nullptr;
        
        bool setupAssemblyPatch() {
            auto base = reinterpret_cast<uint8_t*>(geode::base::get());
            auto baseSize = getBaseSize(); // i have to fix this here.
            
            intptr_t addr = -1;
            std::vector<uint8_t> bytes;
            
            #ifdef GEODE_IS_WINDOWS
            {
                using namespace assembler::x86_64;
                // As shown in eclipse, we have to look for a register or smt
                addr = sinaps::find<"FF 90 ? ? ? ? ^ F3 0F 10 8E ? ? ? ? F3 44 0F 10">(base, baseSize);
                if (addr != sinaps::not_found) {
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
                using namespace assembler::arm64;
                auto func = dlsym(RTLD_DEFAULT, "_ZN15GJBaseGameLayer6updateEf");
                addr = sinaps::find<"0B 19 2B 1E 0F 10 62 1E 00 10 2E 1E">(
                    static_cast<const uint8_t*>(func), 0x500);
                if (addr != sinaps::not_found) {
                    addr += reinterpret_cast<intptr_t>(func) - reinterpret_cast<intptr_t>(base);
                    bytes = Builder(addr)
                        .mov(Register::x9, std::bit_cast<uint64_t>(&g_expectedTicks))
                        .ldr(Register::w0, Register::x9)
                        .b(addr + 0x2c, true)
                        .build();
                }
            }
            #elif defined(GEODE_IS_ANDROID32)
            {
                using namespace assembler::armv7;
                auto func = dlsym(RTLD_DEFAULT, "_ZN15GJBaseGameLayer6updateEf");
                addr = sinaps::find<"B7 EE C7 7A 27 EE 06 7B ^ F7 EE C7 7B 17 EE 90 0A">(
                    static_cast<const uint8_t*>(func), 0x500);
                if (addr != sinaps::not_found) {
                    addr += reinterpret_cast<intptr_t>(func) - reinterpret_cast<intptr_t>(base);
                    bytes = Builder(addr)
                        .mov(Register::r1, std::bit_cast<uint32_t>(&g_expectedTicks))
                        .ldr_t(Register::r0, Register::r1)
                        .nop_t()
                        .build();
                }
            }
            #elif defined(GEODE_IS_IOS) || defined(GEODE_IS_ARM_MAC)
            {
                using namespace assembler::arm64;
                addr = sinaps::find<"00 19 20 1E 02 10 22 1E">(base, baseSize);
                if (addr != sinaps::not_found) {
                    bytes = Builder(addr)
                        .mov(Register::x9, std::bit_cast<uint64_t>(&g_expectedTicks))
                        .ldr(FloatRegister::s0, Register::x9)
                        .pad_nops(20)
                        .build();
                }
            }
            #elif defined(GEODE_IS_INTEL_MAC)
            {
                using namespace assembler::x86_64;
                addr = sinaps::find<"0F 28 C5 F3 0F 5D 83 ? ? ? ? F3 0F 5E D8">(base, baseSize);
                if (addr != sinaps::not_found) {
                    bytes = Builder(addr)
                        .movabs(Register64::rax, std::bit_cast<uint64_t>(&g_expectedTicks))
                        .movss(XmmRegister::xmm0, Register64::rax)
                        .jmp(addr + 0x36, true)
                        .nop(3)
                        .build();
                }
            }
            #endif
            
            // Add the patch (i dont think i did this right)
            if (addr == sinaps::not_found || bytes.empty()) {
                return false;
            }
            
            auto patchResult = geode::Mod::get()->patch(
                reinterpret_cast<void*>(addr + base), bytes);
            if (!patchResult) {
                return false;
            }
            
            m_patch = patchResult.unwrap();
            return true;
        }
        // pretty much taken directly from Eclipse, i should fix this later
    public:
        bool init() {
            if (!setupAssemblyPatch()) {
                geode::log::warn("TPS Bypass: Assembly patching failed, falling back to hooks");
                return false;
            }
            
            if (m_patch) {
                m_patch->disable();
            }
            
            return true;
        }
        
        void setEnabled(bool enabled) {
            if (!m_patch) return;
            
            if (enabled) {
                m_patch->enable();
            } else {
                m_patch->disable();
            }
        }
        
        void updateTPS(float newTPS) {
            // This is where you calculate and set the expected ticks
            // This will be called from your modified update() method
            expectedTicks() = static_cast<TicksType>(newTPS == 240.f ? 1 : //smt here lol);
        }
    };
    
    // then update the delta
    class $modify(GJBaseGameLayer) {
        struct Fields {
            double m_extraDelta = 0.0;
            TPSBypassWithPatches m_tpsPatches;
        };
        
        void update(float dt) override {
            if (!tpsEnabled || tpsValue == 240.f || !PlayLayer::get()) {
                return GJBaseGameLayer::update(dt);
            }
            
            auto fields = m_fields.self();
            
            // find the delta again
            fields->m_extraDelta += dt;
            auto timeWarp = std::min(m_gameState.m_timeWarp, 1.f);
            auto newTPS = tpsValue / timeWarp;
            auto spt = 1.0 / newTPS;  
            auto steps = std::round(fields->m_extraDelta / spt);
            auto totalDelta = steps * spt;
            fields->m_extraDelta -= totalDelta;
            
            expectedTicks() = steps;
            
            GJBaseGameLayer::update(totalDelta);
        }
        
        float getModifiedDelta(float dt) {
            return dt; 
        }
    };
    // ty eciplse, im going to sleep
    class $modify(PlayLayer) {
        void updateProgressbar() {
            auto timestamp = m_level->m_timestamp;
            auto currentProgress = m_gameState.m_currentProgress;
            
            if (timestamp > 0 && tpsValue != 240.f && tpsEnabled) {
                float levelProgress = static_cast<float>(m_gameState.m_currentProgress) / timestamp * 100.f;
                m_gameState.m_currentProgress = timestamp * levelProgress / 100.f;
            }
            
            PlayLayer::updateProgressbar();
            m_gameState.m_currentProgress = currentProgress;
        }
        
        void destroyPlayer(PlayerObject* player, GameObject* object) override {
            auto timestamp = m_level->m_timestamp;
            auto currentProgress = m_gameState.m_currentProgress;
            
            if (timestamp > 0 && tpsValue != 240.f && tpsEnabled) {
                float levelProgress = static_cast<float>(m_gameState.m_currentProgress) / timestamp * 100.f;
                m_gameState.m_currentProgress = timestamp * levelProgress / 100.f;
            }
            
            PlayLayer::destroyPlayer(player, object);
            m_gameState.m_currentProgress = currentProgress;
        }
        
        void levelComplete() {
            auto oldTimestamp = m_gameState.m_unkUint2;
            if (tpsValue != 240.f && tpsEnabled) {
                auto ticks = static_cast<uint32_t>(std::round(m_gameState.m_levelTime * 240));
                m_gameState.m_unkUint2 = ticks;
            }
            PlayLayer::levelComplete();
            m_gameState.m_unkUint2 = oldTimestamp;
        }
    };
}
*/