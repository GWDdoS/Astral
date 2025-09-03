// still needs rewrite dont get me wrong

#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <cmath>

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
        
        float targetDt = 1.0f / fpsValue;
        
        // rework delta time to be toggable like TCBot etc
        GJBaseGameLayer::update(targetDt);
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
            dt = 0.0;
        }

        // Not actually sure what this is smt with timewarp
        float timeWarp = 1.0f;
        if (m_gameState.m_timeWarp <= 1.0f) {
            timeWarp = m_gameState.m_timeWarp;
        }

        double adjustedDt = dt + m_extraDelta;
        float steps = std::round(adjustedDt / (timeWarp * targetDt));
        double finalDt = steps * timeWarp * targetDt;
        m_extraDelta = adjustedDt - finalDt;

        return finalDt;
    }
};