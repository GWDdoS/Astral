// THIS NEEDS A MAJOR UPDATE IN THE FUTURE TO FIX FPS VALUES; NAT FPS FIX AND THE PLATFORM BASED MEM CALC FIX
// eclipse would modify original memory patches or smt
// add lock delta

##include "includes.hpp"
// link fps test
class $modify(GJBaseGameLayer) {
    void update(float dt) override {
        if (!tpsEnabled) {
            cocos2d::CCDirector::sharedDirector()->setAnimationInterval(1.0f / 240.0f);
            return GJBaseGameLayer::update(dt);
        }
        
        if (tpsValue == 240.f) {
            cocos2d::CCDirector::sharedDirector()->setAnimationInterval(1.0f / 240.0f);
            return GJBaseGameLayer::update(dt);
        }
        
        if (!PlayLayer::get()) {
            cocos2d::CCDirector::sharedDirector()->setAnimationInterval(1.0f / 240.0f);
            return GJBaseGameLayer::update(dt);
        }
        
        cocos2d::CCDirector::sharedDirector()->setAnimationInterval(1.0f / tpsValue);
        
        float newDt = 1.f / tpsValue;

        if (framestepEnabled) return GJBaseGameLayer::update(newDt);

        GJBaseGameLayer::update(newDt);
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
        
        return newDt * timeWarp;
    }
};

class $modify(CCDirector) {
    void setAnimationInterval(double interval) override {
        if (tpsEnabled && PlayLayer::get()) {
            interval = 1.0 / tpsValue;
        }
        CCDirector::setAnimationInterval(interval);
    }
};