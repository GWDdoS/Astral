#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoMirrorHook, GJBaseGameLayer) {
    void toggleFlipped(bool p0, bool p1) {
        if (noMirror) {
            return;
        }
        else {
            GJBaseGameLayer::toggleFlipped(p0, p1);
        }
    }
};