#include "../../includes.hpp"

namespace Astral::Hacks::Global {
    
    // i dont really know how this works...? but uhh it kinda does. Need to fix it being really slow and need to fix it not going under 240
      class $modify(GJBaseGameLayer) {
        struct Fields {
            double m_extraDelta = 0.0;
        };

        void update(float dt) override { 
            if (!tpsEnabled || tpsValue == 240.f || !PlayLayer::get()) {
                return GJBaseGameLayer::update(dt);
            }
            
            if (framestepEnabled) {
                return GJBaseGameLayer::update(1.f / tpsValue);
            }
            
            float newDt = 1.f / tpsValue;
            int steps = std::clamp(static_cast<int>(dt / newDt), 1, 4);
            
            for (int i = 0; i < steps; ++i) {
                GJBaseGameLayer::update(newDt);
            }
        }
        
        float getModifiedDelta(float dt) {
            if (!tpsEnabled || tpsValue == 240.f || !PlayLayer::get()) {
                return GJBaseGameLayer::getModifiedDelta(dt);
            }
            
            if (m_resumeTimer > 0) {
                m_resumeTimer--;
                return 0.0f;
            }
            
            float timeWarp = std::min(m_gameState.m_timeWarp, 1.f);
            float newDt = 1.f / tpsValue;
            
            float adjustedDt = dt + m_fields->m_extraDelta;
            float steps = std::round(adjustedDt / (timeWarp * newDt));
            float finalDt = steps * timeWarp * newDt;
            
            m_fields->m_extraDelta = adjustedDt - finalDt;
            return finalDt;
        }
    };
    
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