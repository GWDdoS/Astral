#include "includes.hpp"

using namespace geode::prelude;

class $modify(InstantMirrorGJBGL, GJBaseGameLayer) {
    void toggleFlipped(bool p0, bool p1) {
        if (instantMirror) {
            GJBaseGameLayer::toggleFlipped(p0, true);
        }
        else {
            GJBaseGameLayer::toggleFlipped(p0, p1);
        }
    }
};