#pragma once
#include "../../vars.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

// Pure input structure - no physics data, no fixes
struct PureInput {
    int frame;          // Game frame when input occurred
    int button;         // Button ID (1 = jump, 2 = left, 3 = right)
    bool player2;       // Is this for player 2?
    bool pressed;       // True for press, false for release

    PureInput() = default;
    PureInput(int f, int b, bool p2, bool p) : frame(f), button(b), player2(p2), pressed(p) {}
};

namespace Astral::Bot {
    enum State {
        DISABLED,
        RECORDING,
        PLAYBACK
    };

    // State management
    void setState(State newState);
    State getState();
    
    // Core bot functions
    void Record();
    void Playback();
    void Save();
    void Load(const std::string& path);
    
    // Recording
    void recordInput(int frame, int button, bool player2, bool pressed);
    void clearInputs();
    
    // Playback
    void processPlayback(int currentFrame);
    void restart();
    
    // Checkpoint handling
    void removeInputsAfter(int frame);
    void setPlaybackFrame(int frame);
    
    // File operations
    bool saveToFile(const std::string& path);
    bool loadFromFile(const std::string& path);
    
    // Info
    size_t getInputCount();
    bool isEmpty();
}