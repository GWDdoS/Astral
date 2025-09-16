// my favorite and the most mortant hack
#include "../../includes.hpp"

using namespace geode::prelude;
class $modify (PlayerObject)
{
    void fadeOutStreak2(float p0)
    {
        if (!keepWaveEnabled)
            PlayerObject::fadeOutStreak2(p0);
    }
};