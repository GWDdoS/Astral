#include "../../includes.hpp"



class $modify(NoclipPL, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obstacle) {
        bool isPlayer1 = (player == m_player1);
        bool isPlayer2 = (player == m_player2);
        
        bool shouldNoclip = false;
        
        
        if (noclipEnabled) {
            shouldNoclip = true;
        } else {
            if (isPlayer1 && noclipP1Enabled && noclipEnabled) {
                shouldNoclip = true;
            } else if (isPlayer2 && noclipP2Enabled && noclipEnabled) {
                shouldNoclip = true;
            } 
        }
        
        if (shouldNoclip) {
            if (!m_anticheatSpike) {
                return;
        }
        
        PlayLayer::destroyPlayer(player, obstacle);
    }
};