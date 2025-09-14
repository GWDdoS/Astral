#include "bot.hpp"
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

namespace {
    // Internal state - kept in anonymous namespace for encapsulation
    Astral::Bot::State g_botState = Astral::Bot::State::DISABLED;
    std::vector<PureInput> g_inputs;
    size_t g_playbackIndex = 0;
}

namespace Astral::Bot {

    // State management
    void setState(State newState) {
        if (g_botState == newState) return;
        
        g_botState = newState;
        
        // Simple state management - no game modifications
        if (newState == State::RECORDING) {
            clearInputs();
        } else if (newState == State::PLAYBACK) {
            restart();
        }
    }

    State getState() {
        return g_botState;
    }

    // Main bot functions
    void Record() {
        setState(State::RECORDING);
    }

    void Playback() {
        setState(State::PLAYBACK);
    }

    void Save() {
        // You can implement UI here to get filename, for now using default
        saveToFile("replay.atr");
    }

    void Load(const std::string& path) {
        if (loadFromFile(path)) {
            setState(State::PLAYBACK);
        }
    }

    // Recording functions
    void recordInput(int frame, int button, bool player2, bool pressed) {
        // Just store the input - no processing, no fixes, no modifications
        g_inputs.emplace_back(frame, button, player2, pressed);
    }

    void clearInputs() {
        g_inputs.clear();
    }

    // Playback functions
    void processPlayback(int currentFrame) {
        // Process all inputs for current frame
        while (g_playbackIndex < g_inputs.size() && 
               g_inputs[g_playbackIndex].frame <= currentFrame) {
            
            auto& input = g_inputs[g_playbackIndex];
            
            // Use the EXACT same logic the game uses for real inputs
            auto* gameLayer = GJBaseGameLayer::get();
            if (gameLayer) {
                // This calls the same handleButton that processes real player inputs
                gameLayer->handleButton(input.pressed, input.button, !input.player2);
            }
            
            g_playbackIndex++;
        }
    }

    void restart() {
        g_playbackIndex = 0;
    }

    // Checkpoint handling
    void removeInputsAfter(int frame) {
        g_inputs.erase(
            std::remove_if(g_inputs.begin(), g_inputs.end(),
                [frame](const PureInput& input) { return input.frame > frame; }),
            g_inputs.end()
        );
    }

    void setPlaybackFrame(int frame) {
        g_playbackIndex = 0;
        // Find first input at or after the target frame
        while (g_playbackIndex < g_inputs.size() && 
               g_inputs[g_playbackIndex].frame < frame) {
            g_playbackIndex++;
        }
    }

    // File operations
    bool saveToFile(const std::string& path) {
        std::ofstream file(path, std::ios::binary);
        if (!file) return false;
        
        // Write simple header with Astral signature
        file.write("ASTR", 4);  // Magic bytes for Astral bot
        
        // Write input count
        size_t inputCount = g_inputs.size();
        file.write(reinterpret_cast<const char*>(&inputCount), sizeof(size_t));
        
        // Write inputs (no TPS, no physics data, no fixes)
        for (const auto& input : g_inputs) {
            file.write(reinterpret_cast<const char*>(&input), sizeof(PureInput));
        }
        
        file.close();
        return true;
    }

    bool loadFromFile(const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file) return false;
        
        // Read and verify header
        char header[4];
        file.read(header, 4);
        if (std::string(header, 4) != "ASTR") {
            file.close();
            return false;
        }
        
        // Read input count
        size_t inputCount;
        file.read(reinterpret_cast<char*>(&inputCount), sizeof(size_t));
        
        // Read inputs (that's all we store)
        g_inputs.resize(inputCount);
        for (auto& input : g_inputs) {
            file.read(reinterpret_cast<char*>(&input), sizeof(PureInput));
        }
        
        file.close();
        return true;
    }

    // Info functions
    size_t getInputCount() {
        return g_inputs.size();
    }

    bool isEmpty() {
        return g_inputs.empty();
    }

} // namespace Astral::Bot

// Hook for recording inputs
class $modify(AstralBotRecordHook, GJBaseGameLayer) {
    void handleButton(bool down, int button, bool isPlayer1) {
        // ALWAYS call original first - no modifications to game behavior
        GJBaseGameLayer::handleButton(down, button, isPlayer1);
        
        // Only record the input - don't change anything about how it's processed
        if (Astral::Bot::getState() == Astral::Bot::State::RECORDING) {
            Astral::Bot::recordInput(
                m_gameState.m_currentProgress,  // Current frame
                button,                         // Button pressed
                !isPlayer1,                    // Convert to player2 bool
                down                           // Press or release
            );
        }
    }
};

// Hook for playback
class $modify(AstralBotPlayHook, GJBaseGameLayer) {
    void processCommands(float dt) {
        // ALWAYS call original first - maintain vanilla game behavior
        GJBaseGameLayer::processCommands(dt);
        
        // Only add playback - don't modify existing game logic
        if (Astral::Bot::getState() == Astral::Bot::State::PLAYBACK) {
            Astral::Bot::processPlayback(m_gameState.m_currentProgress);
        }
    }
};

// Hook for level resets
class $modify(AstralBotResetHook, PlayLayer) {
    void resetLevel() {
        // ALWAYS call original first
        PlayLayer::resetLevel();
        
        // Simple bot state management - no game modifications
        if (Astral::Bot::getState() == Astral::Bot::State::RECORDING) {
            Astral::Bot::clearInputs();  // Start fresh recording
        } else if (Astral::Bot::getState() == Astral::Bot::State::PLAYBACK) {
            Astral::Bot::restart();      // Go back to beginning of replay
        }
    }
};

// Hook for checkpoint handling
class $modify(AstralBotCheckpointHook, PlayLayer) {
    void loadFromCheckpoint(CheckpointObject* checkpoint) {
        // ALWAYS call original first - no checkpoint modifications
        PlayLayer::loadFromCheckpoint(checkpoint);
        
        if (Astral::Bot::getState() == Astral::Bot::State::RECORDING) {
            // Remove inputs after checkpoint frame
            Astral::Bot::removeInputsAfter(checkpoint->m_gameState.m_currentProgress);
        } else if (Astral::Bot::getState() == Astral::Bot::State::PLAYBACK) {
            // Reset playback to checkpoint frame
            Astral::Bot::setPlaybackFrame(checkpoint->m_gameState.m_currentProgress);
        }
        
        // No physics fixes, no position corrections, no velocity adjustments
    }
};