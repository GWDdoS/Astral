#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../../includes.h"

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* p1, GameObject* p2) {
        if (noclipEnabled) {
            if (!m_anticheatSpike) {
                // this line having nothing in it is intentional, it's to never call it
            }
        }
    }
};

// will this work? lets find out 