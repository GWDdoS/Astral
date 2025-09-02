#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "includes.h"
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/Geode.hpp>
#include <imgui-cocos.hpp>


/* de3am is a boykisser and a list helper
   Breuhh is also a boykisser and a list helper. (de3am told me to put this) 
*/
// OMG its all gone :sob: 
// omg its all back :D

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        // this runs after imgui has been setup,
        // its a callback as imgui will be re initialized when toggling fullscreen,
        // so use this to setup any themes and or fonts!
    }).draw([] {
        ImGui::Begin("Astral");
		ImGui::Text("Astral Botting:");
        ImGui::Text(" ");
        ImGui::Button("Record Macro");
        ImGui::Button("Save Macro");
        ImGui::Text(" ");
        ImGui::Text("Astral AutoClicker:");
        ImGui::Text(" ");
        ImGui::Button("Start AutoClicker");
        ImGui::Text(" ");
        ImGui::Text("Astral Hacks:");
        ImGui::Text(" ");
        ImGui::Button("NoClip");

        ImGui::End();
    });
}



#ifndef GEODE_IS_IOS
#include <Geode/modify/CCKeyboardDispatcher.hpp>
class $modify(ImGuiKeybindHook, cocos2d::CCKeyboardDispatcher) {
	bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
		if (key == cocos2d::enumKeyCodes::KEY_Alt && isKeyDown) {
			ImGuiCocos::get().toggle();
		}
		return CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
	}
};
#endif