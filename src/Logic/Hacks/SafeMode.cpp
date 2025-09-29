#include "includes.hpp"

using namespace geode::prelude;

class $modify(SafeModePLHook, PlayLayer) {
    void showNewBest(bool newReward, int orbs, int diamonds, bool demonKey, bool noRetry, bool noTitle) {
        if (safeMode) {
            return;
        }
        else {
            PlayLayer::showNewBest(newReward, orbs, diamonds, demonKey, noRetry, noTitle);
        }
    }
    
    void levelComplete() {
        if (safeMode || forceSafeMode) {
            bool testMode = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::levelComplete();
            m_isTestMode = testMode;
        }
        else {
            PlayLayer::levelComplete();
        }
    }
};

class $modify(SafeModeGJGLHook, GJGameLevel) {
    void savePercentage(int p0, bool p1, int p2, int p3, bool p4) {
        if (safeMode || forceSafeMode) {
            return;
        }
        else {
            GJGameLevel::savePercentage(p0, p1, p2, p3, p4);
        }
    }
};