#include "../../includes.hpp"

bool unlockEverything = false;
// main levels (idk who the fuck needs this but its there)
class $modify(GameLevelManager) {
    GJGameLevel* getMainLevel(int levelID, bool dontGetLevelString) {
        auto level = GameLevelManager::getMainLevel(levelID, dontGetLevelString);
        if (unlockAllEnabled && level->m_requiredCoins > 0) {
            level->m_requiredCoins = 0;
        }
        return level;
    }
};
// icon hack
class $modify(GameManager) {
    bool isColorUnlocked(int key, UnlockType type) {
        if (GameManager::isColorUnlocked(key, type)) return true;
        return unlockAllEnabled;
    }

    bool isIconUnlocked(int key, IconType type) {
        if (GameManager::isIconUnlocked(key, type)) return true;
        return unlockAllEnabled;
    }
};
// pracitce music sync
class $modify(GameStatsManager) {
    bool isItemUnlocked(UnlockType type, int key) {
        if (GameStatsManager::isItemUnlocked(type, key)) return true;
        
        if (unlockAllEnabled) {
            if (type == UnlockType::GJItem && ((key >= 16 && key <= 20))) {
                return true;
            }
        }
        
        return false;
    }
};