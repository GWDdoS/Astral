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
	Astral::Components::Begin(200,120,475,350,"Astral");
    
    if (Astral::Components::Button("Record Macro")){
    }
    if (Astral::Components::Button("Save Macro")) {
    }

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
    Astral::Components::LineGap();
    if (Astral::Components::Button("Save Render (Doesn't work YET)")) {
        Astral::Renderer::SaveRender();
    }
    
    
    Astral::Components::End();
}; 

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
// Plutonic you need to do smt here. 
/*
class $modify(ImGuiKeybindHook, cocos2d::CCKeyboardDispatcher) {
	bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
		if (key == cocos2d::enumKeyCodes::KEY_F4 && isKeyDown) {
			ImGuiCocos::get().toggle();
		}
		return CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
	}
*/