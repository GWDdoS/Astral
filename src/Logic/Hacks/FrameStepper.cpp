#include "../../includes.hpp"

bool framestepEnabled = false;

class $modify(GJBaseGameLayer) {
    void update(float dt) override {
        if (!framestepEnabled) {
            return GJBaseGameLayer::update(dt);
        }

        bool canUse = false;
        if (auto playLayer = utils::get<PlayLayer>()) {
            canUse = !playLayer->m_isPaused && !playLayer->m_hasCompletedLevel && 
                    playLayer->m_started && !playLayer->m_player1->m_isDead;
        }
        else if (auto editor = utils::get<LevelEditorLayer>()) {
            canUse = editor->m_playbackMode == PlaybackMode::Playing;
        }

        if (!canUse) {
            return GJBaseGameLayer::update(dt);
        }

        dt = 1.f / 240.f;
        GJBaseGameLayer::update(dt);
    }
};
// stop this from gui code lol
class $modify(FrameStepperKeyHook, cocos2d::CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        if (framestepEnabled && key == cocos2d::enumKeyCodes::KEY_F && isKeyDown && !isKeyRepeat) {
            return true;
        }
        
        return cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};