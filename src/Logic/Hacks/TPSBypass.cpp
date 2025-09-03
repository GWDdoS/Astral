// still needs rewrite dont get me wrong
// this shit should work now
#include "../../includes.hpp"

using namespace geode::prelude;

extern float tpsValue;
extern bool lockDeltaEnabled; // Add this to your main.cpp variables

class $modify(GJBaseGameLayer) {

    void update(float dt) {
        // Don't modify anything if we're at default 240 FPS and lock delta is disabled
        if (tpsValue == 240.0f && !lockDeltaEnabled) {
            return GJBaseGameLayer::update(dt);
        }
        
        // Don't modify if not in a level
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::update(dt);
        }
        
        // Only use fixed delta if lock delta is enabled
        if (lockDeltaEnabled) {
            float fixedDt = 1.0f / tpsValue;
            GJBaseGameLayer::update(fixedDt);
        } else {
            // Use original delta time for smooth high FPS gameplay
            GJBaseGameLayer::update(dt);
        }
    }

    float getModifiedDelta(float dt) {
        // Don't modify anything if we're at default 240 FPS and lock delta is disabled
        if (tpsValue == 240.0f && !lockDeltaEnabled) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }
        
        // Don't modify if not in a level
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }

        // Handle resume timer
        if (0 < m_resumeTimer) {
            m_resumeTimer--;
            return 0.0f;
        }

        // Handle time warp
        float timeWarp = 1.0f;
        if (m_gameState.m_timeWarp <= 1.0f) {
            timeWarp = m_gameState.m_timeWarp;
        }

        if (lockDeltaEnabled) {
            // Use locked delta time
            float targetDt = 1.0f / tpsValue;
            return targetDt * timeWarp;
        } else {
            // For high FPS bypass without locking delta, we need to adjust the physics
            // Scale the original delta to maintain consistent physics speed
            float scaledDt = dt * (tpsValue / 240.0f);
            return GJBaseGameLayer::getModifiedDelta(scaledDt) * timeWarp;
        }
    }
};