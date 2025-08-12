#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "includes.h"
#include <Geode/modify/CCKeyboardDispatcher.hpp>


/* de3am is a boykisser and a list helper
   Breuhh is also a boykisser and a list helper. (de3am told me to put this) 
*/
using namespace geode::prelude;

bool rendering = false;

void setup() {
    Astral::GUI::Theme::Astral();
}
void render() {
	Astral::Components::Begin("Astral");
    
    if (Astral::Components::Button("Record Macro")){
    }
    if (Astral::Components::Button("Save Macro")) {
    }
    Astral::Components::LineGap();
    if (Astral::Components::Button("Test FFMPEG Install")) {
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

// smt for files
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
/*
void setup() {
    static bool m_show = true;

    if (Astral::Components::IsKeyPressed(ImGuiKey_Ctrl)) {
        m_show = !m_show;
    }

    if (m_show == true) {
        Astral::Components::Begin("Hello, ImGui!");

        Astral::Components::Text("This is a simple ImGui window.");
        Astral::Components::Text("You can put any ImGui widgets here.");

        if (Astral::Components::Button("Close")) {
            // This will hide our ImGui interface.
            Astral::Components::get().toggle();
        }


        Astral::Components::End();
    }
} 
*/