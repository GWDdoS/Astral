#include "../../includes.hpp"

class $modify(NoclipPL, PlayLayer) {
    void destroyPlayer(PlayerObject* p0, GameObject* p1) {
        if (noclipEnabled) {
            if (m_anticheatSpike) {
                PlayLayer::destroyPlayer(p0, p1);
            }
        } else {
            PlayLayer::destroyPlayer(p0, p1);
        }
    }
};