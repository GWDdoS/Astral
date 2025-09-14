#include "bot.hpp"
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <chrono>
#include <fstream>
#include <vector>

using namespace geode::prelude;

namespace Astral::Bot {
    
    struct MacroEvent {
        double timestamp;
        bool isPress;
        int button;
        bool isPlayer1;
        float playerPosX;
        float playerPosY;
    };
    
    static std::vector<MacroEvent> recordedMacro;
    static std::vector<MacroEvent> playbackMacro;
    static bool isRecording = false;
    static bool isPlayingBack = false;
    static std::chrono::high_resolution_clock::time_point recordStartTime;
    static std::chrono::high_resolution_clock::time_point playbackStartTime;
    static size_t playbackIndex = 0;
    
    // Get current timestamp in seconds
    double getCurrentTime() {
        auto now = std::chrono::high_resolution_clock::now();
        if (isRecording) {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - recordStartTime);
            return duration.count() / 1000000.0; // Convert to seconds
        } else if (isPlayingBack) {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - playbackStartTime);
            return duration.count() / 1000000.0;
        }
        return 0.0;
    }
    
    // Get player position (you'll need to implement this based on your game layer access)
    std::pair<float, float> getPlayerPosition(bool isPlayer1) {
        // This is a placeholder - you'll need to implement actual player position retrieval
        // You might need to access the current GameLayer and get player positions
        return {0.0f, 0.0f};
    }
    
    void StartRecording() {
        recordedMacro.clear();
        isRecording = true;
        recordStartTime = std::chrono::high_resolution_clock::now();
        log::info("Started macro recording");
    }
    
    void StopRecording() {
        isRecording = false;
        log::info("Stopped macro recording. Events recorded: {}", recordedMacro.size());
    }
    
    void StartPlayback() {
        if (playbackMacro.empty()) {
            playbackMacro = recordedMacro; // Use recorded macro if no specific playback macro loaded
        }
        
        if (playbackMacro.empty()) {
            log::warn("No macro to play back");
            return;
        }
        
        isPlayingBack = true;
        playbackStartTime = std::chrono::high_resolution_clock::now();
        playbackIndex = 0;
        log::info("Started macro playback. Events to play: {}", playbackMacro.size());
    }
    
    void StopPlayback() {
        isPlayingBack = false;
        playbackIndex = 0;
        log::info("Stopped macro playback");
    }
    
    void Save() {
        if (recordedMacro.empty()) {
            log::warn("No macro to save");
            return;
        }
        
        try {
            std::string savePath = (Mod::get()->getSaveDir() / "macro.atr").string();
            std::ofstream file(savePath, std::ios::binary);
            
            if (!file.is_open()) {
                log::error("Failed to open file for saving: {}", savePath);
                return;
            }
            
            // Write header
            uint32_t version = 1;
            uint32_t eventCount = static_cast<uint32_t>(recordedMacro.size());
            
            file.write(reinterpret_cast<const char*>(&version), sizeof(version));
            file.write(reinterpret_cast<const char*>(&eventCount), sizeof(eventCount));
            
            // Write events
            for (const auto& event : recordedMacro) {
                file.write(reinterpret_cast<const char*>(&event), sizeof(MacroEvent));
            }
            
            file.close();
            log::info("Saved macro with {} events to {}", recordedMacro.size(), savePath);
            
        } catch (const std::exception& e) {
            log::error("Error saving macro: {}", e.what());
        }
    }
    
    void Load() {
        try {
            std::string loadPath = (Mod::get()->getSaveDir() / "macro.atr").string();
            std::ifstream file(loadPath, std::ios::binary);
            
            if (!file.is_open()) {
                log::warn("No saved macro found at: {}", loadPath);
                return;
            }
            
            // Read header
            uint32_t version;
            uint32_t eventCount;
            
            file.read(reinterpret_cast<char*>(&version), sizeof(version));
            file.read(reinterpret_cast<char*>(&eventCount), sizeof(eventCount));
            
            if (version != 1) {
                log::error("Unsupported macro file version: {}", version);
                file.close();
                return;
            }
            
            // Read events
            playbackMacro.clear();
            playbackMacro.reserve(eventCount);
            
            for (uint32_t i = 0; i < eventCount; ++i) {
                MacroEvent event;
                file.read(reinterpret_cast<char*>(&event), sizeof(MacroEvent));
                playbackMacro.push_back(event);
            }
            
            file.close();
            log::info("Loaded macro with {} events from {}", playbackMacro.size(), loadPath);
            
        } catch (const std::exception& e) {
            log::error("Error loading macro: {}", e.what());
        }
    }
    
    void Clear() {
        recordedMacro.clear();
        playbackMacro.clear();
        log::info("Cleared all macro data");
    }
    
    // Update function to be called every frame for playback
    void Update() {
        if (!isPlayingBack || playbackIndex >= playbackMacro.size()) {
            return;
        }
        
        double currentTime = getCurrentTime();
        
        // Check if it's time to execute the next event
        while (playbackIndex < playbackMacro.size() && 
               playbackMacro[playbackIndex].timestamp <= currentTime) {
            
            const MacroEvent& event = playbackMacro[playbackIndex];
            
            // Execute the event by calling the game's button handler
            // You'll need to get access to the current GJBaseGameLayer instance
            if (auto* gameLayer = GameManager::get()->getPlayLayer()) {
                gameLayer->handleButton(event.isPress, event.button, event.isPlayer1);
            }
            
            playbackIndex++;
        }
        
        // Check if playback is complete
        if (playbackIndex >= playbackMacro.size()) {
            StopPlayback();
        }
    }
}

class $modify(MacroGJBaseGameLayer, GJBaseGameLayer) {
    void handleButton(bool down, int button, bool isPlayer1) {
        // Record the event if recording is active
        if (Astral::Bot::isRecording) {
            Astral::Bot::MacroEvent event;
            event.timestamp = Astral::Bot::getCurrentTime();
            event.isPress = down;
            event.button = button;
            event.isPlayer1 = isPlayer1;
            
            // Get player position
            auto pos = Astral::Bot::getPlayerPosition(isPlayer1);
            event.playerPosX = pos.first;
            event.playerPosY = pos.second;
            
            Astral::Bot::recordedMacro.push_back(event);
        }
        
        // Call original function
        GJBaseGameLayer::handleButton(down, button, isPlayer1);
    }
    
    void update(float delta) {
        // Call original update first
        GJBaseGameLayer::update(delta);
        
        // Update macro playback
        Astral::Bot::Update();
    }
}