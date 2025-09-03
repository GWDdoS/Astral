
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../../includes.h"

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* p1, GameObject* p2) {
        if (noclipEnabled) {
            // When noclip is enabled, don't destroy the player
            return;
        }
        // When noclip is disabled, call the original function
        PlayLayer::destroyPlayer(p1, p2);
    }
};