#include "../../includes.hpp"

bool framestepEnabled = false;
static bool shouldStep = false;

class $modify(FrameStepperHook, GJBaseGameLayer) {
    void update(float dt) override {
=        if (!framestepEnabled) {
            return GJBaseGameLayer::update(dt);
        }

=        bool canUse = false;
        if (auto playLayer = PlayLayer::get()) {
            canUse = !playLayer->m_isPaused && !playLayer->m_hasCompletedLevel && 
                    playLayer->m_started && !playLayer->m_player1->m_isDead;
        }
        else if (auto editor = LevelEditorLayer::get()) {
            canUse = editor->m_playbackMode == PlaybackMode::Playing;
        }

        if (!canUse) {
            return GJBaseGameLayer::update(dt);
        }

=        if (shouldStep) {
            shouldStep = false; // so u dont just keep stepping
            dt = 1.f / tpsValue;  
        } else {
            dt = 0.f; // idk i was told this would fix it
        }
        
        GJBaseGameLayer::update(dt);
    }
};
// main.cpp copy
class $modify(FrameStepperKeyHook, cocos2d::CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        if (key == cocos2d::enumKeyCodes::KEY_F && isKeyDown && !isKeyRepeat) {
            framestepEnabled = true;
            shouldStep = true;
            return true; 
        }
        
        return cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};