#include "../../includes.hpp"
#include <Geode/modify/PlayLayer.hpp>

class $modify(NoclipPL, PlayLayer) {
    void destroyPlayer(PlayerObject* p0, GameObject* p1) {
        if (noclipEnabled) {
            if (!m_anticheatSpike) {
               
                return;
            }
        }
        PlayLayer::destroyPlayer(p0, p1);
    }
};