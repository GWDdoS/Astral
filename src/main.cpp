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

bool noclipEnabled = false;

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        // this runs after imgui has been setup,
        // its a callback as imgui will be re initialized when toggling fullscreen,
        // so use this to setup any themes and or fonts!
   }).draw([] {
    ImGui::BeginTabBar("##tabs");
    if (ImGui::BeginTabItem("Hacks")) {
        ImGui::Text("Astral Hacks:");
        ImGui::Separator();
        ImGui::Checkbox("Enable Noclip", &noclipEnabled);
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Botting")) {
        ImGui::Text("Astral Botting:");
        ImGui::Separator();
        if (ImGui::Button("Record Macro")) {
            // Add macro recording functionality here
        }
        if (ImGui::Button("Save Macro")) {
            // Add macro saving functionality here  
        }
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("AutoClicker")) {
        ImGui::Text("Astral AutoClicker:");
        ImGui::Separator();
        if (ImGui::Button("Start AutoClicker")) {
            // Add autoclicker functionality here
        }
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
});
}



        
    


// #ifndef GEODE_IS_IOS
class $modify(ImGuiKeybindHook, cocos2d::CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        if (key == cocos2d::enumKeyCodes::KEY_Alt && isKeyDown) {
            ImGuiCocos::get().toggle();
        }
        return cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};
// #endif


/*
ImGui::Tooltip("Astral Mod by de3am and breuhh");
ImGui::Text("Astral Mod by de3am and breuhh");
ImGui::Button(" "); --- IGNORE ---
ImGui::Checkbox("Enable Astral Mod", &astralEnabled); --- IGNORE ---
ImGui::ToggleButton("Enable Astral Mod", &astralEnabled); // New toggle button
*/
