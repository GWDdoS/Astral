#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoDeathEffectHook, PlayerObject) {
    void playDeathEffect() {
        if (noDeathEffect) {
            return;
        }
        else {
            PlayerObject::playDeathEffect();
        }
    }
};