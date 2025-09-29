#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoGhostTrailHook, GhostTrailEffect) {
    void draw() {
        if (ghostTrail) {
            return;
        }
        GhostTrailEffect::draw();
    }
};