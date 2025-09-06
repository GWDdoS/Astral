#include "../includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

static int currentTab = 0;

void renderBottingTab()
{
    ImGui::Text("Botting Features:");
    ImGui::Separator();
    
    if (ImGui::Button("Record Macro", ImVec2(150, 30))) {
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Play Macro", ImVec2(150, 30))) {
    }
    
    ImGui::Spacing();
    ImGui::Text("Macro Settings:");
    static bool loopMacro = false;
    ImGui::Checkbox("Loop Macro", &loopMacro);
}

void renderHacksTab()
{
    ImGui::Text("Hack Features:");
    ImGui::Separator();
    
    ImGui::Checkbox("Enable Noclip", &noclipEnabled);
    ImGui::Checkbox("Enable Speedhack", &speedhackEnabled);
    
    if (speedhackEnabled) {
        ImGui::Text("Speed Multiplier:");
        ImGui::SetNextItemWidth(120);
        ImGui::SliderFloat("##speed", &speedValue, 0.1f, 5.0f, "%.2f");
    }
    
    ImGui::Spacing();
    ImGui::Checkbox("Enable Trajectory", &trajectoryEnabled);
    ImGui::Checkbox("Frame Stepper", &framestepEnabled);
}

void renderAutoClickerTab()
{
    ImGui::Text("AutoClicker Settings:");
    ImGui::Separator();
    
    static bool autoClickerEnabled = false;
    ImGui::Checkbox("Enable AutoClicker", &autoClickerEnabled);
    
    if (autoClickerEnabled) {
        static float clickRate = 20.0f;
        ImGui::Text("Clicks per second:");
        ImGui::SetNextItemWidth(150);
        ImGui::SliderFloat("##clickrate", &clickRate, 1.0f, 1000.0f, "%.1f");
        
        static bool holdToClick = false;
        ImGui::Checkbox("Hold to Click", &holdToClick);
    }
}

void renderRenderTab()
{
    ImGui::Text("Render Features:");
    ImGui::Separator();
    
    ImGui::Checkbox("Show Layout", &layoutEnabled);
    
    if (ImGui::Button("Start Render", ImVec2(150, 30))) {
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Stop Render", ImVec2(150, 30))) {
    }
    
    ImGui::Spacing();
    static bool showHitboxes = false;
    ImGui::Checkbox("Show Hitboxes", &showHitboxes);
    
    static bool showGrid = false;
    ImGui::Checkbox("Show Grid", &showGrid);
}

void renderSettingsTab()
{
    ImGui::Text("GUI Settings:");
    ImGui::Separator();
    
    ImGui::Text("Toggle GUI Key:");
    const char* currentKeyDisplay = getKeyName(capturedCustomKey);
    
    if (ImGui::Button(isCapturingKeybind ? "Press any key..." : currentKeyDisplay, ImVec2(120, 25))) {
        isCapturingKeybind = !isCapturingKeybind;
    }
    
    if (isCapturingKeybind) {
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            isCapturingKeybind = false;
        }
    }
    
    ImGui::Text("Current Key: %s", currentKeyDisplay);
}

void renderCustomizationTab()
{
    ImGui::Text("Customization Options:");
    ImGui::Separator();
    
    ImGui::Text("Theme settings here...");
}

void renderMainGui()
{
    if (ImGui::Begin("Astral")) {
        
        const char* tabNames[] = {"Botting", "Hacks", "AutoClicker", "Render", "Settings", "Customization"};
        const int tabCount = 6;
        
        for (int i = 0; i < tabCount; i++) {
            if (i > 0) ImGui::SameLine();
            
            if (ImGui::Button(tabNames[i], ImVec2(120, 30))) {
                currentTab = i;
            }
        }
        
        ImGui::Separator();
        
        switch (currentTab) {
            case 0: renderBottingTab(); break;
            case 1: renderHacksTab(); break;
            case 2: renderAutoClickerTab(); break;
            case 3: renderRenderTab(); break;
            case 4: renderSettingsTab(); break;
            case 5: renderCustomizationTab(); break;
        }
    }
    ImGui::End();
}