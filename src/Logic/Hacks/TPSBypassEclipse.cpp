// THIS NEEDS A MAJOR UPDATE IN THE FUTURE TO FIX FPS VALUES; NAT FPS FIX AND THE PLATFORM BASED MEM CALC FIX
// eclipse would modify original memory patches or smt
// add lock delta

#include "includes.hpp"
// dora no care fr fr. if this works ill eat my balls
class $modify(TPSBypassGJBGLHook, GJBaseGameLayer) {
    struct Fields {
        double m_extraDelta = 0.0;
    };

    float getCustomDelta(float dt, float tps, bool applyExtraDelta = true) {
        auto spt = 1.f / tps;

        if (applyExtraDelta && m_resumeTimer > 0) {
            --m_resumeTimer;
            dt = 0.f;
        }

        auto totalDelta = dt + m_extraDelta;
        auto timestep = std::min(m_gameState.m_timeWarp, 1.f) * spt;
        auto steps = std::round(totalDelta / timestep);
        auto newDelta = steps * timestep;
        if (applyExtraDelta) m_extraDelta = totalDelta - newDelta;
        return static_cast<float>(newDelta);
    }

    float getModifiedDelta(float dt) {
        if (!tpsEnabled) return GJBaseGameLayer::getModifiedDelta(dt);
        if (tpsValue == 240.f) return GJBaseGameLayer::getModifiedDelta(dt);
        if (!PlayLayer::get()) return GJBaseGameLayer::getModifiedDelta(dt);

        return getCustomDelta(dt, tpsValue);
    }

    void update(float dt) override {
        if (!tpsEnabled) return GJBaseGameLayer::update(dt);
        if (tpsValue == 240.f) return GJBaseGameLayer::update(dt);
        if (!PlayLayer::get()) return GJBaseGameLayer::update(dt);

        auto fields = m_fields.self();
        fields->m_extraDelta += dt;

        // calculate number of steps based on the new TPS
        auto timeWarp = std::min(m_gameState.m_timeWarp, 1.f);
        auto newTPS = tpsValue / timeWarp;

        auto spt = 1.0 / newTPS;
        auto steps = std::round(fields->m_extraDelta / spt);
        auto totalDelta = steps * spt;
        fields->m_extraDelta -= totalDelta;

        GJBaseGameLayer::update(totalDelta);
    }
};

class $modify(TPSBypassPLHook, PlayLayer) {
    int calculationFix() {
        auto timestamp = m_level->m_timestamp;
        auto currentProgress = m_gameState.m_currentProgress;
        
        if (timestamp > 0 && tpsValue != 240.f) {
            // Recalculate m_currentProgress based on the actual time passed
            // Note: You'll need to implement getActualProgress() based on your needs
            // auto progress = getActualProgress(this);
            // m_gameState.m_currentProgress = timestamp * progress / 100.f;
        }
        return currentProgress;
    }

    void updateProgressbar() {
        if (!tpsEnabled || tpsValue == 240.f) {
            return PlayLayer::updateProgressbar();
        }

        auto currentProgress = calculationFix();
        PlayLayer::updateProgressbar();
        m_gameState.m_currentProgress = currentProgress;
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) override {
        if (!tpsEnabled || tpsValue == 240.f) {
            return PlayLayer::destroyPlayer(player, object);
        }

        auto currentProgress = calculationFix();
        PlayLayer::destroyPlayer(player, object);
        m_gameState.m_currentProgress = currentProgress;
    }

    void levelComplete() {
        if (!tpsEnabled || tpsValue == 240.f) {
            return PlayLayer::levelComplete();
        }

        auto oldTimestamp = m_gameState.m_unkUint2;
        auto ticks = static_cast<uint32_t>(std::round(m_gameState.m_levelTime * 240));
        m_gameState.m_unkUint2 = ticks;
        
        PlayLayer::levelComplete();
        m_gameState.m_unkUint2 = oldTimestamp;
    }
};