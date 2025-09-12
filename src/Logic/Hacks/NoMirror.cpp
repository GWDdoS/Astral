#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoMirrorGJBGL, GJBaseGameLayer) {
    void toggleFlipped(bool p1, bool p2) {
        if (noMirror) {
            return;
        }
        else {
            GJBaseGameLayer::toggleFlipped(p1, p2);
        }
    }
};