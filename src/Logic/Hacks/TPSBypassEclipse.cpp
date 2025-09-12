// THIS NEEDS A MAJOR UPDATE IN THE FUTURE TO FIX FPS VALUES; NAT FPS FIX AND THE PLATFORM BASED MEM CALC FIX
// eclipse would modify original memory patches or smt
// add lock delta
bool tpsEnabled;
bool framestepEnabled;
float tpsValue = 240.f;
bool tpsEnabled = true;
bool framestepEnabled = false;

#include "../../includes.hpp"

class $modify(GJBaseGameLayer) {
    void update(float dt) override {

        if (!tpsEnabled) return GJBaseGameLayer::update(dt);
        if (tpsValue == 240.f) return GJBaseGameLayer::update(dt);
        if (!PlayLayer::get()) return GJBaseGameLayer::update(dt);
        
        float newDt = 1.f / tpsValue;

        if (framestepEnabled) return GJBaseGameLayer::update(newDt);

        float realDt = dt; 
        int steps = static_cast<int>(realDt / newDt);
        
        if (steps > 4) steps = 4;
        if (steps < 1) steps = 1;

        auto startTime = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < steps; ++i) {
            GJBaseGameLayer::update(newDt);
            
            auto elapsed = std::chrono::high_resolution_clock::now() - startTime;
            if (elapsed > std::chrono::milliseconds(16)) {
                break;
            }
        }
    }

    float getModifiedDelta(float dt) override {
        if (!tpsEnabled) return GJBaseGameLayer::getModifiedDelta(dt);
        if (tpsValue == 240.f) return GJBaseGameLayer::getModifiedDelta(dt);
        if (!PlayLayer::get()) return GJBaseGameLayer::getModifiedDelta(dt);

        float newDt = 1.f / tpsValue;
        
        if (m_resumeTimer > 0) {
            m_resumeTimer--;
            return 0.0f;
        }

        float timeWarp = (m_gameState.m_timeWarp <= 1.0f) ? m_gameState.m_timeWarp : 1.0f;
        
        float adjustedDt = dt + m_extraDelta;
        float steps = std::round(adjustedDt / (timeWarp * newDt));
        float finalDt = steps * timeWarp * newDt;
        
        m_extraDelta = adjustedDt - finalDt;
        
        return finalDt;
    }
};