#include <Geode/Geode.hpp>
#include "includes.h"

using namespace geode::prelude;

void setup() {
    //Echo2::GUI::GetTheme();
}

void render() {
	Echo2::Components::Begin(80, 120, 520, 430, "Echo v2");

    Echo2::Components::Button("Hi");

    Echo2::Components::End();
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup(setup).draw(render);
}