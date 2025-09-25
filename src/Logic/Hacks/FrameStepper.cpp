#include "../../includes.hpp"

bool framestepEnabled = false;
static bool shouldStep = false;

class $modify(FrameStepperHook, GJBaseGameLayer) {
    static void onModify(auto& self) {
    FIRST_PRIORITY("cocos2d::CCScheduler::update"); // according to AI, this is becuase gd engine clamps the delta, so if i run it before it locks, it will work
    }
    void update(float dt) override {
        if (!framestepEnabled) {
            return GJBaseGameLayer::update(dt);
        }

        bool canUse = false;
        if (auto playLayer = PlayLayer::get()) {
            canUse = !playLayer->m_isPaused && !playLayer->m_hasCompletedLevel && 
                    playLayer->m_started && !playLayer->m_player1->m_isDead;
        }
        if (!canUse) {
            return GJBaseGameLayer::update(dt);
        }

        if (shouldStep) {
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