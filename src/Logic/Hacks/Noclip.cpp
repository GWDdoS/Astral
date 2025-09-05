#include "../../includes.hpp"

// noclipEnabled = false;
// noclipP1 = false;
// noclipP2 = false;

class $modify(NoclipPL, PlayLayer)
{
    void destroyPlayer(PlayerObject *player, GameObject *obstacle)
    {
        bool isPlayer1 = (player == m_player1);
        bool isPlayer2 = (player == m_player2);
        bool shouldNoclip = false;

        if (noclipEnabled)
        {
            shouldNoclip = true;
        }
        else
        {
            if (isPlayer1 && noclipP1 && noclipEnabled)
            {
                shouldNoclip = true;
            }
            else if (isPlayer2 && noclipP2 && noclipEnabled)
            {
                shouldNoclip = true;
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
};

/*
if (ImGui::Combo("Noclip Mode", &noclipMode, "Off\0Both Players\0Player 1 Only\0Player 2 Only\0")){
                        switch (noclipMode)
                                {
                            case 0: // Off
                                noclipEnabled = false;
                                noclipP1 = false;
                                noclipP2 = false;
                                break;

                            case 1: // Both Players
                                noclipEnabled = true;
                                noclipP1 = true;
                                noclipP2 = true;
                                break;

                            case 2: // Player 1 Only
                                noclipEnabled = true;
                                noclipP1 = true;
                                noclipP2 = false;
                                break;

                            case 3: // Player 2 Only
                                noclipEnabled = true;
                                noclipP1 = false;
                                noclipP2 = true;
                            break;
                        }
                    }
*/
