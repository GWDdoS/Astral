#include "includes.hpp"

// noclipEnabled = false;
// noclipP1 = false;
// noclipP2 = false;

class $modify(NoclipPL, PlayLayer)
{
    void destroyPlayer(PlayerObject* player, GameObject* obstacle)
    {
        if (noclipEnabled)
        {
        bool shouldNoclip = false;

        {
            if (player == m_player1)
            {
                shouldNoclip = noclipP1;
            }
            else if (player == m_player2)
            {
                shouldNoclip = noclipP2;
            }
            else if (player == m_player1 && player == m_player2)
            {
                shouldNoclip = noclipP1 && noclipP2;
            }
        }

        if (shouldNoclip)
        {
            if (obstacle == m_anticheatSpike)
            {
                PlayLayer::destroyPlayer(player, obstacle);
            }
            else
            {
                return;
            }
        }
    if (!shouldNoclip) {
        PlayLayer::destroyPlayer(player, obstacle);
    }
    }
  }
};