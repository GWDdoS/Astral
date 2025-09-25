#include "../../includes.hpp"
// todo, add mem patches for <240 tps. 
// idk if these fixes work but here we are
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

    float getModifiedDelta(float dt) override {
        if (!tpsEnabled || tpsValue == 240.f) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }

        auto timeWarp = std::min(m_gameState.m_timeWarp, 1.f);
        auto spt = 1.f / tpsValue;

        if (m_resumeTimer > 0) {
            --m_resumeTimer;
            dt = 0.f;
        }

        auto fields = m_fields.self();
        auto totalDelta = dt + fields->m_extraDelta;
        auto timestep = timeWarp * spt;
        auto steps = std::round(totalDelta / timestep);
        auto newDelta = steps * timestep;
        fields->m_extraDelta = totalDelta - newDelta;
        
        return static_cast<float>(newDelta);
    }
};

void updateTPSSettings() {
    if (!tpsEnabled) {
        auto* director = cocos2d::CCDirector::sharedDirector();
        director->setAnimationInterval(1.f / 60.f);
        return;
    }

    auto* director = cocos2d::CCDirector::sharedDirector();
    float frameTime = 1.f / tpsValue;
    director->setAnimationInterval(frameTime);
}

class $modify(TPSBypassPLHook, PlayLayer) {
    void updateProgressbar() override {
        auto timestamp = m_level->m_timestamp;
        auto currentProgress = m_gameState.m_currentProgress;
        
        if (timestamp > 0 && tpsEnabled && tpsValue != 240.f) {
            auto actualProgress = static_cast<float>(m_gameState.m_currentProgress) / timestamp * 100.f;
            m_gameState.m_currentProgress = timestamp * actualProgress / 100.f;
        }
        
        PlayLayer::updateProgressbar();
        m_gameState.m_currentProgress = currentProgress;
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) override {
        auto timestamp = m_level->m_timestamp;
        auto currentProgress = m_gameState.m_currentProgress;
        
        if (timestamp > 0 && tpsEnabled && tpsValue != 240.f) {
            auto actualProgress = static_cast<float>(m_gameState.m_currentProgress) / timestamp * 100.f;
            m_gameState.m_currentProgress = timestamp * actualProgress / 100.f;
        }
        
        PlayLayer::destroyPlayer(player, object);
        m_gameState.m_currentProgress = currentProgress;
    }

    void levelComplete() override {
        auto oldTimestamp = m_gameState.m_unkUint2;
        
        if (tpsEnabled && tpsValue != 240.f) {
            auto ticks = static_cast<uint32_t>(std::round(m_gameState.m_levelTime * 240));
            m_gameState.m_unkUint2 = ticks;
        }
        
        PlayLayer::levelComplete();
        m_gameState.m_unkUint2 = oldTimestamp;
    }
};