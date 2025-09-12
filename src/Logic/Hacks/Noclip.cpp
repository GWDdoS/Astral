#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoclipPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (noclipEnabled) {
            if (player == m_player1) {
                shouldNoclip = noclipP1;
            }
            else if (player == m_player2) {
                shouldNoclip = noclipP2;
            }

            if (shouldNoclip) {
                if (object == m_anticheatSpike) {
                    PlayLayer::destroyPlayer(player, object);
                }
                    return;
                }
            }
        }
    }
};