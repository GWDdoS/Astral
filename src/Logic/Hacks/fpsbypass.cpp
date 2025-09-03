// still needs rewrite dont get me wrong
// this shit should work now
#include "../../includes.hpp"

using namespace geode::prelude;

extern float fpsValue;

class $modify(GJBaseGameLayer) {

    void update(float dt) {
        if (fpsValue == 240.0f) {
            return GJBaseGameLayer::update(dt);
        }
        
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::update(dt);
        }
        
        float fixedDt = 1.0f / fpsValue;
        
        GJBaseGameLayer::update(fixedDt);
    }

    float getModifiedDelta(float dt) {
        if (fpsValue == 240.0f) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }
        
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }

        float targetDt = 1.0f / fpsValue;
        
        if (0 < m_resumeTimer) {
            m_resumeTimer--;
            return 0.0f;
        }
        // copied from XDBot
        float timeWarp = 1.0f;
        if (m_gameState.m_timeWarp <= 1.0f) {
            timeWarp = m_gameState.m_timeWarp;
        }

        return targetDt * timeWarp;
    }
};