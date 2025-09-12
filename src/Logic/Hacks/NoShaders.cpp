#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoShaderLayer, ShaderLayer) {
    void performCalculations() {
        if (noShaders) {
            m_state.m_usesShaders = false;
        }
    }
};