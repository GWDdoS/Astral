#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include "includes.h"

// de3am is a boykisser

/* de3am is a boykisser and a list helper
   Breuhh is also a boykisser and a list helper. (de3am told me to put this) 
*/
using namespace geode::prelude;

bool rendering = false;


@@ -47,27 +47,31 @@ $on_mod(Loaded) {
    if (!std::filesystem::exists(RendersDir()))
        std::filesystem::create_directories(RendersDir());
}

// de3am is a boykisser

class $modify(MenuLayer) {
    void onMoreGames(CCObject* target) {
        Astral_GUI_Mobile_UI::create()->show();
    }
};

$execute {
    using namespace keybinds;

    BindManager::get()->registerBindable({
        "open-astral"_spr,
        "Toggle Astral",
        "Toggle the Astral UI.",
        { Keybind::create(cocos2d::enumKeyCodes::KEY_P, Modifier::Alt) },
        "CORE Bot"
    });
    new EventListener([=](InvokeBindEvent* event) {
        if (event->isDown()) ImGuiCocos::get().toggle();
        return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "open-imgui"_spr));
}
void draw() {
    static bool m_show = true;

    if (ImGui::IsKeyPressed(ImGuiKey_LeftShift)) {
        m_show = !m_show;
    }

    if (m_show == true) {
        ImGui::Begin("Hello, ImGui!");

        ImGui::Text("This is a simple ImGui window.");
        ImGui::Text("You can put any ImGui widgets here.");

        if (ImGui::Button("Close")) {
            /* This will hide our ImGui interface. */
            ImGuiCocos::get().toggle();
        }


        ImGui::End();
    }
} 


