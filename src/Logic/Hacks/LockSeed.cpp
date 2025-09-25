#include "../../includes.hpp"

bool seedHackEnabled = false;
int seedValue = 1;

$hook(GameToolbox) {
    float fast_rand_0_1() {
        if (!seedHackEnabled)
            return GameToolbox::fast_rand_0_1();   // keeps old seed if enabled


        int seed = static_cast<int>(seedValue);
        int newSeed = (214013 * seed) + 2531011;
        return ((newSeed >> 16) & 0x7FFF) / 32767.f;
    }
};