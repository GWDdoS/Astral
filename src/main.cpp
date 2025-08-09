#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "includes.h"

/* de3am is a boykisser and a list helper
   Breuhh is also a boykisser and a list helper. (de3am told me to put this) 
*/
using namespace geode::prelude;

bool rendering = false;

void setup() {
    Astral::GUI::Theme::Astral
    ();
}
// The REAL GUI THING IS HERE
void render() {
	Astral::Components::Begin(80, 120, 520, 430, "Astral");

    if (Astral::Components::Button("Test")) {
        Astral::Renderer::InstallFFmpeg();
    }

    if (Astral::Components::Button("Render")) {
        if(!rendering) {
            rendering = true;
        } else {
            rendering = false;
        }
    }
    
    if (Astral::Components::Button("Save Render (Doesn't work YET)")) {
        Astral::Renderer::SaveRender();
    }

    Astral::Components::End();
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup(setup).draw(render);

    if (!std::filesystem::exists(AstralPath()))
        std::filesystem::create_directories(AstralPath());
    
    if (!std::filesystem::exists(FFmpegDir()))
        std::filesystem::create_directories(FFmpegDir());

    if (!std::filesystem::exists(RendersDir()))
        std::filesystem::create_directories(RendersDir());
}
class $modify(MenuLayer) {
    void onMoreGames(CCObject* target) {
        Astral_GUI_Mobile_UI::create()->show();
    }
};

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