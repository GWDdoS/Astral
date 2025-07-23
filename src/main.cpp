#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "includes.h"

// de3am is a boykisser

using namespace geode::prelude;

bool rendering = false;

void setup() {
    Core::GUI::Theme::Core();
    
    if (!std::filesystem::exists(CorePath()))
        std::filesystem::create_directories(CorePath());
    
    if (!std::filesystem::exists(FFmpegDir()))
        std::filesystem::create_directories(FFmpegDir());

    if (!std::filesystem::exists(RendersDir()))
        std::filesystem::create_directories(RendersDir());
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
    
    if (Core::Components::Button("Save Render (Doesn't work YET)")) {
        Core::Renderer::SaveRender();
    }

    Core::Components::End();
}

$on_mod(Loaded) {
 //   ImGuiCocos::get().setup(setup).draw(render);
}

// de3am is a boykisser

class $modify(MenuLayer) {
    void onMoreGames(CCObject* target) {
        Core_GUI_Mobile_UI::create()->show();
    }
};