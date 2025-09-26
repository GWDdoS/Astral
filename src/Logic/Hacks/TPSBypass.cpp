#include "../../includes.hpp"

class $modify(TPSBypassGJBGLHook, GJBaseGameLayer) {
    struct Fields {
        double m_extraDelta = 0.0;
    };

    void update(float dt) override {
        if (!tpsEnabled || tpsValue == 240.f) {
            return GJBaseGameLayer::update(dt);
        }

        if (framestepEnabled) {
            return GJBaseGameLayer::update(dt);
        }

        auto fields = m_fields.self();
        fields->m_extraDelta += dt;

        auto timeWarp = std::min(m_gameState.m_timeWarp, 1.f);
        auto effectiveTPS = tpsValue / timeWarp;
        auto secondsPerTick = 1.0 / effectiveTPS;
        
        auto steps = std::round(fields->m_extraDelta / secondsPerTick);
        auto totalDelta = steps * secondsPerTick;
        fields->m_extraDelta -= totalDelta;

        GJBaseGameLayer::update(static_cast<float>(totalDelta));
    }
};

void updateTPSSettings() {
    auto* director = cocos2d::CCDirector::sharedDirector();
    if (!tpsEnabled) {
        director->setAnimationInterval(1.f / 60.f);
    } else {
        director->setAnimationInterval(1.f / tpsValue);
    }
}