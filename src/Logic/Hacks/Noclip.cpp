#include "../../includes.hpp"

// Add variables for individual player noclip control
extern bool noclipP1Enabled;
extern bool noclipP2Enabled;

class $modify(NoclipPL, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obstacle) {
        // Check which player is being destroyed
        bool isPlayer1 = (player == m_player1);
        bool isPlayer2 = (player == m_player2);
        
        // Determine if noclip should apply to this specific player
        bool shouldNoclip = false;
        if (isPlayer1 && (noclipEnabled || noclipP1Enabled)) {
            shouldNoclip = true;
        } else if (isPlayer2 && (noclipEnabled || noclipP2Enabled)) {
            shouldNoclip = true;
        }
        
        if (shouldNoclip) {
            // When noclip is enabled for this player, only allow death from anticheat spikes
            if (m_anticheatSpike) {
                PlayLayer::destroyPlayer(player, obstacle);
            }
            // Don't call PlayLayer::destroyPlayer for regular obstacles
            // This prevents the player from dying to normal spikes, blocks, etc.
            return;
        } else {
            // When noclip is disabled for this player, allow normal death behavior
            PlayLayer::destroyPlayer(player, obstacle);
        }
    }
};