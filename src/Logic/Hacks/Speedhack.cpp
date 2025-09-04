#include "../../includes.hpp"

// External variables from main.cpp
extern bool speedhackEnabled;
extern bool speedhackAudio;
extern float currentPitch;
extern float currentSpeedValue;
extern float speedValue;

void updatePitch(float value) {
  if (!speedhackAudio) {
    if (currentPitch != 1.f) value = 1.f;
    else return;
  }

  FMODAudioEngine* fmod = FMODAudioEngine::sharedEngine();
  FMOD::ChannelGroup* channel = nullptr;
  fmod->m_system->getMasterChannelGroup(&channel);

  if (channel) {
    channel->setPitch(value);
    currentPitch = value;
  }
}

void updateGameSpeed(float value) {
  // Get the director and current scene
  auto director = cocos2d::CCDirector::sharedDirector();
  if (!director) return;
  
  auto scene = director->getRunningScene();
  if (!scene) return;
  
  // Set the game speed by modifying the scheduler time scale
  director->getScheduler()->setTimeScale(value);
  
  // Also update audio pitch if enabled
  if (speedhackAudio) {
    updatePitch(value);
  }
  
  currentSpeedValue = value;
}

void toggleSpeedhack() {
  speedhackEnabled = !speedhackEnabled;

  if (speedhackEnabled) {
    // Apply the current speed value when enabling speedhack
    updateGameSpeed(speedValue);
  } else {
    // Reset to normal speed when disabling speedhack
    updateGameSpeed(1.0f);
    updatePitch(1.0f);
  }
}

void toggleSpeedhackAudio() {
  speedhackAudio = !speedhackAudio;
  
  // Update audio immediately based on current settings
  if (speedhackEnabled) {
    if (speedhackAudio) {
      updatePitch(speedValue);
    } else {
      updatePitch(1.0f);
    }
  }
}