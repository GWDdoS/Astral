// THIS NEEDS A MAJOR UPDATE IN THE FUTURE TO FIX FPS VALUES; NAT FPS FIX AND THE PLATFORM BASED MEM CALC FIX
// eclipse would modify original memory patches or smt
// add lock delta

#include "../../includes.hpp"

class $modify(TPSBypassGJBGLHook, GJBaseGameLayer) {
    struct Fields {
        double m_extraDelta = 0.0;
    };

    void update(float dt) override {
        if (tpsValue <= 0.f) {
            tpsValue = 240.f;
            GJBaseGameLayer::update(dt);
            return;
        }
        
        auto fields = m_fields.self();
        fields->m_extraDelta += dt;
        auto timeWarp = std::min(m_gameState.m_timeWarp, 1.f);
        auto newTPS = tpsValue / timeWarp;
        auto spt = 1.0 / newTPS;
        auto steps = std::round(fields->m_extraDelta / spt);
        auto totalDelta = steps * spt;
        fields->m_extraDelta -= totalDelta;

        GJBaseGameLayer::update(totalDelta);
    }
};


/* we should rewrite these at the least

class $modify(TPSBypassPLHook, PlayLayer) {
    // fix percentage calculation also got this from eclipse who would have known
    int calculationFix() {
        auto timestamp = m_level->m_timestamp;
        auto currentProgress = m_gameState.m_currentProgress;
        if (timestamp > 0 && tpsValue != 240.f) {
            auto progress = (m_gameState.m_levelTime * tpsValue) / timestamp * 100.f;
            m_gameState.m_currentProgress = timestamp * progress / 100.f;
        }
        return currentProgress;
    }
    // fixes progress bar, also got this from eclipse
    void updateProgressbar() {
        auto currentProgress = calculationFix();
        PlayLayer::updateProgressbar();
        m_gameState.m_currentProgress = currentProgress;
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) override {
        auto currentProgress = calculationFix();
        PlayLayer::destroyPlayer(player, object);
        m_gameState.m_currentProgress = currentProgress;
    }
    // fixes level time or smt. I got this from eclipse
    void levelComplete() {
        auto oldTimestamp = m_gameState.m_unkUint2;
        if (tpsValue != 240.f) {
            auto ticks = static_cast<uint32_t>(std::round(m_gameState.m_levelTime * 240));
            m_gameState.m_unkUint2 = ticks;
        }
        PlayLayer::levelComplete();
        m_gameState.m_unkUint2 = oldTimestamp;
    }
};
*/