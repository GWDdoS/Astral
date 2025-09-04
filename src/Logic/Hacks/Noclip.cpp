#include "../../includes.hpp"



class $modify(NoclipPL, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obstacle) {
        bool isPlayer1 = (player == m_player1);
        bool isPlayer2 = (player == m_player2);
        
        bool shouldNoclip = false;
        if (isPlayer1 && (noclipEnabled || noclipP1Enabled)) {
            shouldNoclip = true;
        } else if (isPlayer2 && (noclipEnabled || noclipP2Enabled)) {
            shouldNoclip = true;
        }
        
        if (shouldNoclip) {
            if (!m_anticheatSpike) {
                return;
            }
        }
        else {
            PlayLayer::destroyPlayer(player, obstacle);
        }
    }
};