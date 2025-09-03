// still needs rewrite dont get me wrong
// this shit should work now
#include "../../includes.hpp"

using namespace geode::prelude;


class $modify(GJBaseGameLayer) {

    void update(float dt) {
        if (tpsValue == 240.0f && !lockDeltaEnabled) {
            return GJBaseGameLayer::update(dt);
        }
        
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::update(dt);
        }
        
        if (lockDeltaEnabled) {
            float fixedDt = 1.0f / tpsValue;
            GJBaseGameLayer::update(fixedDt);
        } else {
            GJBaseGameLayer::update(dt);
        }
    }

    float getModifiedDelta(float dt) {
        if (tpsValue == 240.0f && !lockDeltaEnabled) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }
        
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }

        if (0 < m_resumeTimer) {
            m_resumeTimer--;
            return 0.0f;
        }

        float timeWarp = 1.0f;
        if (m_gameState.m_timeWarp <= 1.0f) {
            timeWarp = m_gameState.m_timeWarp;
        }

        if (lockDeltaEnabled) {
            float targetDt = 1.0f / tpsValue;
            return targetDt * timeWarp;
        } else {
            float scaledDt = dt * (tpsValue / 240.0f);
            return GJBaseGameLayer::getModifiedDelta(scaledDt) * timeWarp;
        }
    }
};