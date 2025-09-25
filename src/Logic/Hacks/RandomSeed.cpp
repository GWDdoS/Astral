#include "../../includes.hpp"
// for random ofc, but tbh i have no clue how needed this is lol. copied from eclipse for now

bool seedHackEnabled = false;
float seedValue = 1.0f;
class $modify(GameToolbox) {
    float fast_rand_0_1() {
        if (!seedHackEnabled) {
            return GameToolbox::fast_rand_0_1();
        }
        
        int seed = static_cast<int>(seedValue);
        int newSeed = (214'013 * seed) + 2'531'011;
        return ((newSeed >> 16) & 0x7FFF) / 32767.f;
    }
};