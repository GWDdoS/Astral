#pragma once
#include "../../vars.h"
#include <vector>
#include <chrono>

namespace Astral::Bot {
    
    // MacroEvent struct definition
    struct MacroEvent {
        double timestamp;
        bool isPress;
        int button;
        bool isPlayer1;
        float playerPosX;
        float playerPosY;
    };
    
    // Recording functions
    void StartRecording();
    void StopRecording();
    
    // Playback functions
    void StartPlayback();
    void StopPlayback();
    
    // File operations
    void Save();
    void Load();
    void Clear();
    
    // Update function (called every frame)
    void Update();
    
    // Utility functions
    double getCurrentTime();
    std::pair<float, float> getPlayerPosition(bool isPlayer1);
    
    // External variables that need to be accessible from GUI
    extern std::vector<MacroEvent> recordedMacro;
    extern std::vector<MacroEvent> playbackMacro;
    
    // External variables for state checking
    extern bool isRecording;
    extern bool isPlayingBack;
}