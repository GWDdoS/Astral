#include "../../includes.hpp"

bool seedHackEnabled = false;
int seedValue = 1;

class $hook(GameToolboxFastRandHook, float()) {
    ALL_DELEGATES_AND_SAFE_PRIO("seedhack") // anoterh one of those fixes lmao. 
    float fast_rand_0_1() {
        if (!seedHackEnabled)
            return GameToolbox::fast_rand_0_1();   // keeps old seed if enabled


        int seed = static_cast<int>(seedValue);
        int newSeed = (214013 * seed) + 2531011;
        return ((newSeed >> 16) & 0x7FFF) / 32767.f;
    }
};