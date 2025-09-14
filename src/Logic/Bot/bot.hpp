#pragma once
#include "../../vars.h"
#include <vector>
#include <chrono>

namespace Astral::Bot {
    
    // Forward declarations
    struct MacroEvent;
    
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
    extern bool isRecording;
    extern bool isPlayingBack;
}