#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoShadersHook, ShaderLayer) {
    void performCalculations() {
        if (noShaders) {
            m_state.m_usesShaders = false;
            return;
        }
        ShaderLayer::performCalculations();
    }
};