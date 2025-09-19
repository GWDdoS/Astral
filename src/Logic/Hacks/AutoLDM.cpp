
#include "../../includes.hpp"

// reminder to update this later
class $modify(EditLevelLayer) {
    bool init(GJGameLevel* level) {
        level->m_lowDetailModeToggled = true;
        return EditLevelLayer::init(level);
    }
};

class $modify(LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        level->m_lowDetailModeToggled = true;
        return LevelInfoLayer::init(level, challenge);
    }
};