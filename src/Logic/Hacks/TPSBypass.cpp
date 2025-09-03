// still needs rewrite dont get me wrong
// this shit should work now
#include "../../includes.hpp"

using namespace geode::prelude;

extern float tpsValue;
extern bool lockDeltaEnabled;

class $modify(GJBaseGameLayer) {

    void update(float dt) {
        // Don't modify if at default 240 TPS and lock delta is disabled
        if (tpsValue == 240.0f && !lockDeltaEnabled) {
            return GJBaseGameLayer::update(dt);
        }
        
        // Don't modify if not in a level
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::update(dt);
        }
        
        // Calculate target delta time
        float targetDt = 1.0f / tpsValue;
        
        // Always feed the target dt into update - this is key!
        // This ensures consistent physics regardless of lock delta setting
        GJBaseGameLayer::update(targetDt);
    }

    float getModifiedDelta(float dt) {
        // Don't modify if at default 240 TPS and lock delta is disabled
        if (tpsValue == 240.0f && !lockDeltaEnabled) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }
        
        // Don't modify if not in a level
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }

        // Call original function first to handle internal state changes
        // This is CRITICAL - the original function does important internal work
        GJBaseGameLayer::getModifiedDelta(dt);

        // Handle resume timer
        if (0 < m_resumeTimer) {
            m_resumeTimer--;
            return 0.0f;
        }

        // Handle time warp (clamp to 1.0 max like the original)
        float timeWarp = fminf(m_gameState.m_timeWarp, 1.0f);

        if (lockedDeltaEnabled) {
            // Locked delta: return exact target delta with time warp
            float targetDt = 1.0f / tpsValue;
            return targetDt * timeWarp;
        } else {
            // Unlocked delta: scale based on TPS ratio
            // This maintains smooth gameplay at high TPS
            float baseDt = 1.0f / 240.0f;  // Base GD delta
            float scaledDt = baseDt * (tpsValue / 240.0f);
            return scaledDt * timeWarp;
        }
    }
};