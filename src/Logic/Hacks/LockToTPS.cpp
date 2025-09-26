#include "../../includes.hpp"

bool fpsEnabled = true;
float fpsValue = tpsValue;

void updateFPS() {
    auto* gm = GameManager::sharedState();
    auto* director = cocos2d::CCDirector::sharedDirector();
    
    if (fpsEnabled) {
        gm->setGameVariable("0116", true);
        gm->m_customFPSTarget = fpsValue;
        director->setAnimationInterval(1.f / fpsValue);
    } else {
        gm->setGameVariable("0116", false);
        director->setAnimationInterval(1.f / 60.f);
    }
}