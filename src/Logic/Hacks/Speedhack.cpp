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

void Global::toggleSpeedhack() {
  auto& g = Global::get();
  g.mod->setSavedValue("macro_speedhack_enabled", !g.mod->getSavedValue<bool>("macro_speedhack_enabled"));
  g.speedhackEnabled = g.mod->getSavedValue<bool>("macro_speedhack_enabled");

  if (g.layer) {
    if (static_cast<RecordLayer*>(g.layer)->speedhackToggle)
      static_cast<RecordLayer*>(g.layer)->speedhackToggle->toggle(g.mod->getSavedValue<bool>("macro_speedhack_enabled"));
  }

  if (!g.mod->getSavedValue<bool>("macro_speedhack_enabled"))
    Global::updatePitch(1.f);
}
