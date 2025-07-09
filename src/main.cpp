#include <Geode/Geode.hpp>
#include "includes.h"

// de3am is a boykisser

using namespace geode::prelude;

bool rendering = false;

void setup() {
    //Core::GUI::GetTheme();
    
    if (!std::filesystem::exists(CorePath()))
        std::filesystem::create_directories(CorePath());
    
    if (!std::filesystem::exists(FFmpegDir()))
        std::filesystem::create_directories(FFmpegDir());
}

void render() {
	Core::Components::Begin(80, 120, 520, 430, "Core");

    if (Core::Components::Button("Test")) {
        Core::Renderer::InstallFFmpeg();
    }

    if (Core::Components::Button("Render")) {
        if(!rendering) {
            rendering = true;
        } else {
            rendering = false;
        }
    }

    Core::Components::End();
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup(setup).draw(render);
}