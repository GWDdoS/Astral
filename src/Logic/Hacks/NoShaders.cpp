#include "includes.hpp"

using namespace geode::prelude;

class $modify(NoShaderLayer, ShaderLayer) {
    void performCalculations() {
        m_state.m_usesShaders = !noShaders;
    }
};