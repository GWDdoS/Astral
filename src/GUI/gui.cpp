#include "../includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

static int currentTab = 0;

void applyBackgroundTheme()
{
    auto &style = ImGui::GetStyle();
}

void setupImGuiStyle()
{
    auto& style = ImGui::GetStyle();
    auto& io = ImGui::GetIO();
    auto* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((Mod::get()->getResourcesDir() / ("font" + std::to_string(fontType) + ".ttf")).string().c_str(), 16.0f);

    styleApplied = true;
}

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
}

void renderHacksTab()
{
    ImGui::Text("Hack Features:");
    ImGui::Separator();
    
    ImGui::Checkbox("Enable Noclip", &noclipEnabled);
    ImGui::Checkbox("Enable Speedhack", &speedhackEnabled);

    ImGui::Spacing();
    ImGui::Checkbox("Enable Trajectory", &trajectoryEnabled);
    ImGui::Checkbox("Frame Stepper", &framestepEnabled);
}

void renderAutoClickerTab()
{
    
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
    
    ImGui::Text("Accent Color:");
    ImGui::ColorEdit3("##accentcolor", themeColor);
}

void renderMainGui()
{
    if (styleApplied) { 
    }
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
    
    bool currentGuiState = ImGuiCocos::get().isVisible();
    if (currentGuiState != guiVisible) {
        guiVisible = currentGuiState;
    }
    
    
    if (ImGui::Begin("Astral [BETA]")) {
        
        }
        
        ImGui::SetCursorPosY(70);
        
        const char* tabNames[] = {"Botting", "Hacks", "AutoClicker", "Render", "Settings", "Customization"};
        const int tabCount = 6;
        
        float totalTabWidth = (120 * tabCount) + (ImGui::GetStyle().ItemSpacing.x * (tabCount - 1));
        
    
        ImGui::Separator();
        ImGui::Spacing();
        
        switch (currentTab) {
            case 0: renderBottingTab(); break;
            case 1: renderHacksTab(); break;
            case 2: renderAutoClickerTab(); break;
            case 3: renderRenderTab(); break;
            case 4: renderSettingsTab(); break;
            case 5: renderCustomizationTab(); break;
        }
            ImGui::End();
    }
    