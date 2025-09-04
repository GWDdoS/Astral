#include "../../includes.hpp"

void Global::updatePitch(float value) {
  auto& g = Global::get();
  if (!g.speedhackAudio) {
    if (g.currentPitch != 1.f) value = 1.f;
    else return;
  }

  FMODAudioEngine* fmod = FMODAudioEngine::sharedEngine();
  FMOD::ChannelGroup* channel = nullptr;
  fmod->m_system->getMasterChannelGroup(&channel);

  if (channel) {
    channel->setPitch(value);
    g.currentPitch = value;
  }
}

void Global::updateGameSpeed(float value) {
  auto& g = Global::get();
  
  // Get the current scene
  auto scene = cocos2d::CCScene::getRunningScene();
  if (!scene) return;
  
  // Find the GameManager or PlayLayer to modify game speed
  auto director = cocos2d::CCDirector::sharedDirector();
  if (!director) return;
  
  // Set the game speed by modifying the scheduler time scale
  director->getScheduler()->setTimeScale(value);
  
  // Also update audio pitch if enabled
  if (g.speedhackAudio) {
    Global::updatePitch(value);
  }
  
  g.currentSpeedValue = value;
}

void Global::toggleSpeedhack() {
  auto& g = Global::get();
  g.mod->setSavedValue("macro_speedhack_enabled", !g.mod->getSavedValue<bool>("macro_speedhack_enabled"));
  g.speedhackEnabled = g.mod->getSavedValue<bool>("macro_speedhack_enabled");

  if (g.layer) {
    if (static_cast<RecordLayer*>(g.layer)->speedhackToggle)
      static_cast<RecordLayer*>(g.layer)->speedhackToggle->toggle(g.mod->getSavedValue<bool>("macro_speedhack_enabled"));
  }

  if (g.speedhackEnabled) {
    // Apply the current speed value when enabling speedhack
    Global::updateGameSpeed(g.speedValue);
  } else {
    // Reset to normal speed when disabling speedhack
    Global::updateGameSpeed(1.0f);
    Global::updatePitch(1.0f);
  }
}

void Global::toggleSpeedhackAudio() {
  auto& g = Global::get();
  g.mod->setSavedValue("macro_speedhack_audio", !g.mod->getSavedValue<bool>("macro_speedhack_audio"));
  g.speedhackAudio = g.mod->getSavedValue<bool>("macro_speedhack_audio");
  
  // Update audio immediately based on current settings
  if (g.speedhackEnabled) {
    if (g.speedhackAudio) {
      Global::updatePitch(g.speedValue);
    } else {
      Global::updatePitch(1.0f);
    }
  }
}