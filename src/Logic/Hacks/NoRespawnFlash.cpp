#include "includes.hpp"

using namespace geode::prelude;

class $modify(PlayerObject) {
    void playSpawnEffect() {
        if (noRespawnFlash) {
            return;
        }
        else {
            PlayerObject::playSpawnEffect();
        }
    }
};