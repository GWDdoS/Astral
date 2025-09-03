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
        
        float speedMultiplier = fpsValue / 240.0f;
        float adjustedDt = dt * speedMultiplier;
        
        GJBaseGameLayer::update(adjustedDt);
    }

    float getModifiedDelta(float dt) {
        if (fpsValue == 240.0f) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }
        
        if (!PlayLayer::get()) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }

        float speedMultiplier = fpsValue / 240.0f;
        
        if (0 < m_resumeTimer) {
            m_resumeTimer--;
            dt = 0.0;
        }

        // timewarp or smt 
        float timeWarp = 1.0f;
        if (m_gameState.m_timeWarp <= 1.0f) {
            timeWarp = m_gameState.m_timeWarp;
        }

        double adjustedDt = (dt * speedMultiplier) + m_extraDelta;
        float targetDt = 1.0f / 240.0f;
        float steps = std::round(adjustedDt / (timeWarp * targetDt));
        double finalDt = steps * timeWarp * targetDt;
        m_extraDelta = adjustedDt - finalDt;

        return finalDt;
    }
};