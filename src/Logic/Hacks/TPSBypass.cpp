// still needs rewrite dont get me wrong
// this shit doesnt work
#include "/includes.hpp"

using namespace geode::prelude;



class $modify(GJBaseGameLayer) {

    void update(float dt) {
        if (tpsValue == 240.0f && !lockedDeltaEnabled) {
            return GJBaseGameLayer::update(dt);
        }
        
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::update(dt);
        }
        
        float targetDt = 1.0f / tpsValue;
        
        GJBaseGameLayer::update(targetDt);
    }

    float getModifiedDelta(float dt) {
        if (tpsValue == 240.0f && !lockedDeltaEnabled) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }
        
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }
        GJBaseGameLayer::getModifiedDelta(dt);

        if (0 < m_resumeTimer) {
            m_resumeTimer--;
            return 0.0f;
        }

        float timeWarp = fminf(m_gameState.m_timeWarp, 1.0f);

        if (lockedDeltaEnabled) {
            float targetDt = 1.0f / tpsValue;
            return targetDt * timeWarp;
        } else {
            float baseDt = 1.0f / 240.0f;  
            float scaledDt = baseDt * (tpsValue / 240.0f);
            return scaledDt * timeWarp;
        }
    }
};