#include "../../incudes.hpp"
bool framestepEnabled = false;

namespace Astral::Hacks::Global {
    class $hack(TPSBypass) {
        public:
        void init() override {
            config::setIfEmpty("global.tpsbypass", 240.f);
            
            auto tab = gui::MenuTab::find("tab.global");
            tab->addFloatToggle("global.tpsbypass", 0.f, -1.f, "%.2f TPS") // does this mean its infinte? idk i dont want it to be -1 
            ->handleKeybinds();
        }
        
        [[nodiscard]] const char* getId() const override { return "TPS Bypass"; }
        [[nodiscard]] int32_t getPriority() const override { return -15; }
        
        [[nodiscard]] bool isCheating() const override {
            auto tpsToggle = config::get<bool>("global.tpsbypass.toggle", false);
            auto tps = config::get<float>("global.tpsbypass", 240.f);
            return tpsToggle && tps != 240.f;
        }
    };
}

REGISTER_HACK(TPSBypass)

class $modify(GJBaseGameLayer) {
    struct Fields {
        double m_extraDelta = 0.0;
    };
    
    void update(float dt) override {
        if (!tpsEnabled || tpsValue == 240.f || !PlayLayer::get()) {
            return GJBaseGameLayer::update(dt);
        }
        
        if (framestepEnabled) {
            return GJBaseGameLayer::update(1.f / tpsValue);
        }
        
        float newDt = 1.f / tpsValue;
        int steps = std::clamp(static_cast<int>(dt / newDt), 1, 4);
        
        for (int i = 0; i < steps; ++i) {
            GJBaseGameLayer::update(newDt);
        }
    }
    
    float getModifiedDelta(float dt) {
        if (!tpsEnabled || tpsValue == 240.f || !PlayLayer::get()) {
            return GJBaseGameLayer::getModifiedDelta(dt);
        }
        
        if (m_resumeTimer > 0) {
            m_resumeTimer--;
            return 0.0f;
        }
        
        float timeWarp = std::min(m_gameState.m_timeWarp, 1.f);
        float newDt = 1.f / tpsValue;
        
        float adjustedDt = dt + m_fields->m_extraDelta;
        float steps = std::round(adjustedDt / (timeWarp * newDt));
        float finalDt = steps * timeWarp * newDt;
        
        m_fields->m_extraDelta = adjustedDt - finalDt;
        return finalDt;
    }
};

// def didnt take this from astral. idk what to do tbh
class $modify(PlayLayer) {
    void updateProgressbar() {
        auto timestamp = m_level->m_timestamp;
        auto currentProgress = m_gameState.m_currentProgress;
        
        if (timestamp > 0 && config::get<float>("global.tpsbypass", 240.f) != 240.f) {
            auto progress = utils::getActualProgress(this);
            m_gameState.m_currentProgress = timestamp * progress / 100.f;
        }
        
        PlayLayer::updateProgressbar();
        m_gameState.m_currentProgress = currentProgress;
    }
    
    void destroyPlayer(PlayerObject* player, GameObject* object) override {
        auto timestamp = m_level->m_timestamp;
        auto currentProgress = m_gameState.m_currentProgress;
        
        if (timestamp > 0 && config::get<float>("global.tpsbypass", 240.f) != 240.f) {
            auto progress = utils::getActualProgress(this);
            m_gameState.m_currentProgress = timestamp * progress / 100.f;
        }
        
        PlayLayer::destroyPlayer(player, object);
        m_gameState.m_currentProgress = currentProgress;
    }
    
    void levelComplete() {
        auto oldTimestamp = m_gameState.m_unkUint2;
        if (config::get<float>("global.tpsbypass", 240.f) != 240.f) {
            auto ticks = static_cast<uint32_t>(std::round(m_gameState.m_levelTime * 240));
            m_gameState.m_unkUint2 = ticks;
        }
        PlayLayer::levelComplete();
        m_gameState.m_unkUint2 = oldTimestamp;
    }
};