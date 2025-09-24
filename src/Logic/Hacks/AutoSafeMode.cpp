#include "includes.hpp"

using namespace geode::prelude;

bool autoSafeMode = false;
bool forceSafeMode = false;

void updateAutoSafe() {
    if (autoSafeMode) {
        bool shouldBeSafe = noclipEnabled || autoClickerEnabled;
        
        if (shouldBeSafe) {
            forceSafeMode = true;
        }
    }
}