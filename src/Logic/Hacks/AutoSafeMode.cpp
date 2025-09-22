#include "includes.hpp"

using namespace geode::prelude;

bool autoSafeMode = false;


void updateAutoSafe() {
    if (autoSafeMode) {
        bool shouldBeSafe = noclipEnabled || autoClickerEnabled;
        
        if (shouldBeSafe && !safeMode) {
            safeMode = true;
        }
        else if (!shouldBeSafe && safeMode) {
            safeMode = false;
        }
    }
}

class $modify(SafeLayer, PlayLayer) {
    void showNewBest(bool newReward, int orbs, int diamonds, bool demonKey, bool noRetry, bool noTitle) {
        if (safeMode) {
            return;
        }
        else {
            PlayLayer::showNewBest(newReward, orbs, diamonds, demonKey, noRetry, noTitle);
        }
    }
    
    void levelComplete() {
        updateAutoSafe();
        
        if (safeMode || noclipEnabled) {
            bool testMode = m_isTestMode;
            m_isTestMode = true;
            PlayLayer::levelComplete();
            m_isTestMode = testMode;
        }
        else {
            PlayLayer::levelComplete();
        }
    }
    class $modify(SafeGJGameLevel, GJGameLevel) {
        void savePercentage(int p0, bool p1, int p2, int p3, bool p4) {
            if (safeMode) {
                return;
            }
            else {
                GJGameLevel::savePercentage(p0, p1, p2, p3, p4);
            }
        }
    };
};