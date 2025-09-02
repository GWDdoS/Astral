#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "includes.h"

using namespace geode::prelude;

class $modify(MyPlaylayer, PlayLayer) {
    void destroyPlayer(PlayerObject* p1, GameObject* p2) {
        if (!&noclipEnabled) {
            if (!m_anticheatSpike) {
                PlayLayer::destroyPlayer(p1, p2);
            }
        }
    }
};

// will this work? lets find out 