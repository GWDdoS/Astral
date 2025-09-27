#include "includes.hpp"
using namespace geode::prelude;
float frameCount = 0.0f;
bool initialized = false;
static float lastLevelTime = 0.0f;
static float lastProgress = 0.0f;


float getCurrentFrame() {
    auto* playLayer = PlayLayer::get();
    if (!playLayer) {
        frameCount = 0.0f;
        initialized = false;
        lastLevelTime = 0.0f;
        lastProgress = 0.0f;
        return 0.0f;
    }
    
    float currentTime = playLayer->m_gameState.m_levelTime;
    float currentProgress = playLayer->m_gameState.m_currentProgress;
    
    if (initialized && (currentProgress < lastProgress - 0.01f || currentTime < lastLevelTime - 0.01f)) {
        frameCount = 0.0f;
        initialized = false;
        lastLevelTime = 0.0f;
    }
    
    if (!playLayer->m_hasCompletedLevel && 
        !playLayer->m_isPaused && 
        currentProgress > 0.0f) {
        
        if (!initialized) {
            initialized = true;
            frameCount = 0.0f;
        }
        
        frameCount += 1.0f;
    }
    
    lastProgress = currentProgress;
    lastLevelTime = currentTime;
    
    return frameCount;
}
class $modify(PlayLayer) {
    void update(float dt) {
        PlayLayer::update(dt);
        getCurrentFrame();
    }
};