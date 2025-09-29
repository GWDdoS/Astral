#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoGhostTrailHook, PlayerObject) {
    void toggleGhostEffect(GhostType p0) {
        if (ghostTrail) {
            p0 = GhostType::Disabled;
            PlayerObject::toggleGhostEffect(p0);
        }
        else {
            p0 = GhostType::Enabled;
            PlayerObject::toggleGhostEffect(p0);
        }
    }
};