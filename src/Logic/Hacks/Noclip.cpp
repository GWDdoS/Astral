#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../../includes.h"

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* p1, GameObject* p2) {
        if (noclipEnabled) {
            if (!m_anticheatSpike) {
                // Don't call the original destroyPlayer when noclip is enabled
                return;
            }
        }
        // Call the original destroyPlayer when noclip is disabled
        PlayLayer::destroyPlayer(p1, p2);
    }
};