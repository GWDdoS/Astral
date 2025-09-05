#include "../includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

void applyBackgroundTheme()
{
    auto &style = ImGui::GetStyle();
    
    switch (backgroundTheme)
    {
        case 0:                                                                   // Dark
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.75f); // 75% opacity
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.75f);  // 75% opacity
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.18f, 0.18f, 0.8f);
        style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
        break;
        case 1:                                                                   // Light
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.75f); // 75% opacity
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.96f, 0.96f, 0.96f, 0.75f);  // 75% opacity
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.94f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.9f, 0.9f, 0.9f, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.85f, 0.85f, 0.85f, 0.8f);
        style.Colors[ImGuiCol_Text] = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
        break;
        case 2:                                                                  // Medium
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.3f, 0.3f, 0.3f, 0.75f);   // 75% opacity
        style.Colors[ImGuiCol_ChildBg] = ImVec4(0.35f, 0.35f, 0.35f, 0.75f); // 75% opacity
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.3f, 0.3f, 0.3f, 0.94f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.45f, 0.45f, 0.45f, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.55f, 0.55f, 0.55f, 0.8f);
        style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
        break;
    }
}

void setupImGuiStyle()
{
    auto& style = ImGui::GetStyle();
    auto& io = ImGui::GetIO();
    auto* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((Mod::get()->getResourcesDir() / ("font" + std::to_string(fontType) + ".ttf")).string().c_str(), 16.0f);
    // notice the font + fontType. Artifact of the old code that tried to swap fonts.

    io.FontGlobalScale = 1.0f;
    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 4.0f;
    style.ChildRounding = 4.0f;
    style.ScaleAllSizes(1.0f);
    
    ImVec4 baseGreen = ImVec4(0.2f, 0.7f, 0.4f, 1.0f); 
    ImVec4 darkBaseGreen = ImVec4(0.15f, 0.5f, 0.3f, 1.0f);  
    ImVec4 lightBaseGreen = ImVec4(0.25f, 0.8f, 0.5f, 1.0f);  
    ImVec4 baseAccent = ImVec4(0.1f, 0.6f, 0.35f, 1.0f);  
    
    applyBackgroundTheme();
    
    style.Colors[ImGuiCol_TitleBg] = darkBaseGreen;
    style.Colors[ImGuiCol_TitleBgActive] = baseGreen;
    style.Colors[ImGuiCol_Button] = darkBaseGreen;
    style.Colors[ImGuiCol_ButtonHovered] = baseGreen;
    style.Colors[ImGuiCol_ButtonActive] = baseAccent;
    style.Colors[ImGuiCol_FrameBgActive] = baseAccent;
    style.Colors[ImGuiCol_CheckMark] = baseGreen;
    style.Colors[ImGuiCol_SliderGrab] = baseGreen;
    style.Colors[ImGuiCol_SliderGrabActive] = lightBaseGreen;
    style.Colors[ImGuiCol_Header] = darkBaseGreen;
    style.Colors[ImGuiCol_HeaderHovered] = baseGreen;
    style.Colors[ImGuiCol_HeaderActive] = lightBaseGreen;
    style.Colors[ImGuiCol_Tab] = darkBaseGreen;
    style.Colors[ImGuiCol_TabHovered] = baseGreen;
    style.Colors[ImGuiCol_TabActive] = lightBaseGreen;
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1f, 0.4f, 0.25f, 0.8f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = darkBaseGreen;
    
    styleApplied = true;
}

void renderMainGui()
{
    if (styleApplied) {
        auto& style = ImGui::GetStyle();
        ImVec4 customColor = ImVec4(themeColor[0], themeColor[1], themeColor[2], 1.0f);
        ImVec4 customColorDark = ImVec4(themeColor[0] * 0.6f, themeColor[1] * 0.7f, themeColor[2] * 0.7f, 1.0f); 
        ImVec4 customColorLight = ImVec4(
            std::min(1.0f, themeColor[0] * 1.3f), 
            std::min(1.0f, themeColor[1] * 1.1f), 
            std::min(1.0f, themeColor[2] * 1.2f), 
            1.0f
        );
        
        style.Colors[ImGuiCol_TitleBgActive] = customColor;
        style.Colors[ImGuiCol_ButtonHovered] = customColor;
        style.Colors[ImGuiCol_CheckMark] = customColor;
        style.Colors[ImGuiCol_SliderGrab] = customColor;
        style.Colors[ImGuiCol_HeaderHovered] = customColor;
        style.Colors[ImGuiCol_TabHovered] = customColor;
        style.Colors[ImGuiCol_Button] = customColorDark;
        style.Colors[ImGuiCol_Header] = customColorDark;
        style.Colors[ImGuiCol_Tab] = customColorDark;
        style.Colors[ImGuiCol_SliderGrabActive] = customColorLight;
        style.Colors[ImGuiCol_HeaderActive] = customColorLight;
        style.Colors[ImGuiCol_TabActive] = customColorLight;
    }
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    
    bool currentGuiState = ImGuiCocos::get().isVisible();
    if (currentGuiState != guiVisible) {
        guiVisible = currentGuiState;
    }
    
    ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    
    if (ImGui::Begin("Astral Mod", nullptr, window_flags)) {
        
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        
        ImU32 col_top = IM_COL32(0, 0, 0, 255);        // Black at top
        ImU32 col_bottom = IM_COL32(80, 80, 80, 255);  // Grey at bottom
        
        draw_list->AddRectFilledMultiColor(
            windowPos,
            ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
            col_top, col_top, col_bottom, col_bottom
        );
        
        
        ImGui::Text("Categories:");
        if (ImGui::Button("Botting", ImVec2(80, 25))) {}
        ImGui::SameLine();
        if (ImGui::Button("Hacks", ImVec2(80, 25))) {}
        ImGui::SameLine();
        if (ImGui::Button("AutoClicker", ImVec2(80, 25))) {}
        ImGui::SameLine();
        if (ImGui::Button("Render", ImVec2(80, 25))) {}
        ImGui::SameLine();
        if (ImGui::Button("Settings", ImVec2(80, 25))) {
        }
        ImGui::SameLine();
        if (ImGui::Button("Customization", ImVec2(100, 25))) {}
        
        ImGui::Separator();
        
        ImGui::Text("GUI Settings:");
        
        ImGui::Text("Toggle GUI Key:");
        const char* currentKeyDisplay = getKeyName(capturedCustomKey);
        
        if (ImGui::Button(isCapturingKeybind ? "Press any key..." : currentKeyDisplay, ImVec2(120, 0))) {
            isCapturingKeybind = !isCapturingKeybind;
        }
        
        if (isCapturingKeybind) {
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                isCapturingKeybind = false;
            }
        }
        
        ImGui::Text("Current Key: %s", currentKeyDisplay);
        
        ImGui::Spacing();
        
        ImGui::Text("Other Settings:");
        ImGui::SetNextItemWidth(120);
        static int classic_mode = 0;
        ImGui::Combo("##classic", &classic_mode, "Classic\0Modern\0");
        
        ImGui::SameLine();
        ImGui::Text("Theme Style");
        
        ImGui::Spacing();
        
        ImGui::Checkbox("Enable Noclip", &noclipEnabled);
        ImGui::SameLine();
        ImGui::Checkbox("Show Layout", &layoutEnabled);
        
        ImGui::Checkbox("Enable Speedhack", &speedhackEnabled);
        if (speedhackEnabled) {
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80);
            ImGui::InputFloat("##speed", &speedValue, 0.1f, 1.0f, "%.1f");
        }
        
        ImGui::Checkbox("Enable Trajectory", &trajectoryEnabled);
        ImGui::SameLine();
        ImGui::Checkbox("Frame Stepper", &framestepEnabled);
        
        ImGui::Separator();
        if (ImGui::Button("Record Macro", ImVec2(100, 0))) {}
        ImGui::SameLine();
        if (ImGui::Button("Start Render", ImVec2(100, 0))) {}
        ImGui::SameLine();
        if (ImGui::Button("AutoClicker", ImVec2(100, 0))) {}
    }
    ImGui::End();
}