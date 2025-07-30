#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "includes.h"

// de3am is a boykisser

using namespace geode::prelude;

bool rendering = false;

void setup() {
    Core::GUI::Theme::Core();
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
    ImGuiCocos::get().setup(setup).draw(render);

    if (!std::filesystem::exists(CorePath()))
        std::filesystem::create_directories(CorePath());
    
    if (!std::filesystem::exists(FFmpegDir()))
        std::filesystem::create_directories(FFmpegDir());

    if (!std::filesystem::exists(RendersDir()))
        std::filesystem::create_directories(RendersDir());
}

// de3am is a boykisser

class $modify(MenuLayer) {
    void onMoreGames(CCObject* target) {
        Core_GUI_Mobile_UI::create()->show();
    }
};
$execute {
    using namespace keybinds;

    BindManager::get()->registerBindable({
        "open-core"_spr,
        "Toggle CORE",
        "Toggle the CORE UI.",
        { Keybind::create(cocos2d::enumKeyCodes::KEY_P, Modifier::Alt) },
        "CORE Bot"
    });
    new EventListener([=](InvokeBindEvent* event) {
        if (event->isDown()) ImGuiCocos::get().toggle();
        return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "open-imgui"_spr));
}