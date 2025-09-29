#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoRespawnFlashPOHook, PlayerObject) {
    void playSpawnEffect() {
        if (noRespawnFlash) {
            return;
        }
        else {
            PlayerObject::playSpawnEffect();
        }
    }
};