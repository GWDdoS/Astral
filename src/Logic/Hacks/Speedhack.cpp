#include "../../includes.hpp"

float speedhackMultiplier = 1.0f;


class $modify(SpeedhackSchedulerHook, cocos2d::CCScheduler) {
    void update(float dt) override {
        if (speedhackEnabled) {
            CCScheduler::update(dt * speedhackMultiplier);
        } else {
            CCScheduler::update(dt);
        }
    }
};