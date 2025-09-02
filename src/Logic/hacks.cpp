#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* p0, GameObject* p1) {
        if (!m_anticheatSpike) {
            log::info("balls"); // this is not required i just thought it was funny
        }
    }
};