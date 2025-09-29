#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoOrbRingHook, RingObject) {
    void spawnCircle() {
        if (noOrbEffectEnabled && noOrbRing) {
            return;
        }
        RingObject::spawnCircle();
    }
};

class $modify(NoOrbHitEffectHook, PlayerObject) {
    void ringJump(RingObject *p0, bool p1) {
        if (noOrbEffectEnabled && noOrbHitEffect) {
            bool orig = m_maybeReducedEffects;
            m_maybeReducedEffects = true;
            PlayerObject::ringJump(p0, p1);
            m_maybeReducedEffects = orig;
            return;
        }
        PlayerObject::ringJump(p0, p1);
    }
};