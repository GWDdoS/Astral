#include "../../includes.hpp"
using namespace geode::prelude;

bool seedHackEnabled = false;
float seedValue = 1.0f;
class $modify(GameToolbox) {
    #ifdef GEODE_IS_WINDOWS 
    // windows code here
    #else
    float fast_rand_0_1() {
        if (!seedHackEnabled)
            return GameToolbox::fast_rand_0_1();   // keeps old seed if enabled


        int seed = static_cast<float>(seedValue);
        int newSeed = (214013 * seed) + 2531011;
        return ((newSeed >> 16) & 0x7FFF) / 32767.f;
    }
    #endif
};