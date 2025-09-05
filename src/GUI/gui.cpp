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
    auto* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((Mod::get()->getResourcesDir() / "font"+fontType+".ttf").string().c_str(), 16.0f);

    io.FontGlobalScale = 1.0f;
    style.WindowRounding = 12.0f;
    style.FrameRounding = 8.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 8.0f;
    style.GrabRounding = 8.0f;
    style.TabRounding = 8.0f;
    style.ChildRounding = 8.0f;
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

void renderBottingTab()
{
    ImGui::Separator();
    ImGui::InputText("Macro Name", macroName, sizeof(macroName));
    if (ImGui::Button("Record Macro", ImVec2(120, 0))) {
    }
    ImGui::SameLine();
    if (ImGui::Button("Save Macro", ImVec2(120, 0))) {
    }
    ImGui::Spacing();
    ImGui::Text("TPS Bypass:");
    ImGui::SetNextItemWidth(150);
    ImGui::InputFloat("TPS", &tpsValue);
    ImGui::Checkbox("Lock Delta Time", &lockedDeltaEnabled);
    ImGui::Separator();
    ImGui::Text("Speedhack Controls:");
    ImGui::Checkbox("Enable Speedhack", &speedhackEnabled);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(150);
    ImGui::InputFloat("Speed Value", &speedValue, 0.1f, 1.0f, "%.2f");
    ImGui::Checkbox("Audio Sync", &speedhackAudio);
    ImGui::Spacing();
    ImGui::Checkbox("Enable Trajectory", &trajectoryEnabled);
    
    ImGui::Checkbox("Frame Stepper", &framestepEnabled);
    
    if (ImGui::Button("Step Frame", ImVec2(120, 0))) {
    }
    
    ImGui::Checkbox("Enable 2.1 Legacy Physics", &oldphysEnabled);
}

void renderHacksTab()
{
    ImGui::Separator();
    ImGui::Checkbox("Enable Noclip", &noclipEnabled);
    ImGui::SetNextItemWidth(150);
    if (ImGui::Combo("Noclip Mode", &noclipMode, "Both Players\0Player 1\0Player 2\0")){
        switch (noclipMode)
        {
            case 0: // Both Players
            noclipP1 = true;
            noclipP2 = true;
            break;
            
            case 1: // Player 1 Only
            noclipP1 = true;
            noclipP2 = false;
            break;
            
            case 2: // Player 2 Only
            noclipP1 = false;
            noclipP2 = true;
            break;
        }
    }
    ImGui::Separator();
    ImGui::Checkbox("Show Layout", &layoutEnabled);
    ImGui::SetNextItemWidth(150);
    ImGui::InputFloat("Lock Seed", &seedValue);
}

void renderAssistsTab()
{
    ImGui::Separator();
    if (ImGui::Button("Start AutoClicker", ImVec2(140, 0))) {
    }
    if (ImGui::Button("Stop AutoClicker", ImVec2(140, 0))) {
    }
    if (ImGui::Button("Dual Merge Input", ImVec2(140, 0))) {
    }
    ImGui::SetNextItemWidth(150);
    ImGui::Combo("Input Type", &inputMerge, "Input\0Space\0Up\0Left\0Right\0");
}

void renderRenderTab()
{
    ImGui::Separator();
    if (ImGui::Button("Start Render", ImVec2(120, 0))) {
    }
    if (ImGui::Button("Stop Render", ImVec2(120, 0))) {
    }
}

void renderSettingsTab()
{
    ImGui::Separator();
    ImGui::Text("GUI Settings:");
    ImGui::Separator();
    
    ImGui::Text("Toggle GUI Key:");
    
    const char* currentKeyDisplay = getKeyName(capturedCustomKey);
    
    if (ImGui::Button(isCapturingKeybind ? "Press any key..." : "Set Keybind")) {
        isCapturingKeybind = !isCapturingKeybind;
    }
    
    // get pressed key (it works....?)
    if (isCapturingKeybind) {
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            isCapturingKeybind = false;
        }
        ImGui::Text("Press any key to set as keybind (ESC to cancel)");
        ImGui::Text("Waiting for input...");
    }
    
    ImGui::Text("Current Key: %s", currentKeyDisplay);
}

void renderCustomizationTab()
{
    ImGui::Separator();
    ImGui::Text("Theme Color:");
    if (ImGui::ColorEdit3("##themecolor", themeColor)) {
    }
    
    if (ImGui::Button("Reset to Default", ImVec2(150, 0))) {
        themeColor[0] = 0.2f; // R
        themeColor[1] = 0.7f; // G  
        themeColor[2] = 0.4f; // B
    }
    ImGui::Separator();
    ImGui::Text("Background Theme:");
    ImGui::SetNextItemWidth(150);
    if (ImGui::Combo("##backgroundtheme", &backgroundTheme, backgroundThemeNames, backgroundThemeNamesCount)) {
        applyBackgroundTheme();
    }
    // I think we need a new applyBackgroundTheme; applyFont?
    ImGui::Text("Font:");
    ImGui::SetNextItemWidth(150);
    if (ImGui::Combo("Font Type", &fontList, "Font 1\0Font 2\0Font 3\0")){
        switch (fontList)
        {
            case 0: // font 1
                fontType = 0;
                break;
            
            case 1: // font 2
                fontType = 1;
                break;
            
            case 2: // font 3
                fontType = 2;
                break;
        }
    }
    ImGui::Separator();
    ImGui::Button("De3am Mode");
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
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    
    bool currentGuiState = ImGuiCocos::get().isVisible();
    if (currentGuiState != guiVisible) {
        guiVisible = currentGuiState;
    }
    
    ImGui::SetNextWindowSize(ImVec2(600, 450), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    
    if (ImGui::Begin("Astral Mod", nullptr, window_flags)) {
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 windowPos = ImGui::GetWindowPos();
        
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 banner_min = windowPos;
        ImVec2 banner_max = ImVec2(windowPos.x + windowSize.x, windowPos.y + 40);
        
        ImVec4 bannerColor = ImVec4(themeColor[0], themeColor[1], themeColor[2], 0.8f);
        draw_list->AddRectFilled(banner_min, banner_max, ImGui::ColorConvertFloat4ToU32(bannerColor), 12.0f, ImDrawFlags_RoundCornersTop);
        
        const char* title = "Astral [Alpha]";
        ImVec2 text_size = ImGui::CalcTextSize(title);
        ImVec2 text_pos = ImVec2(
            windowPos.x + (windowSize.x - text_size.x) * 0.5f,
            windowPos.y + (50 - text_size.y) * 0.5f
        );
        
        draw_list->AddText(text_pos, IM_COL32(255, 255, 255, 255), title);
        
        ImGui::Dummy(ImVec2(0, 50));
        
        ImGui::BeginChild("MainContent", ImVec2(0, -5), false, ImGuiWindowFlags_NoScrollbar);
        
        ImGui::BeginChild("TabsPanel", ImVec2(140, 0), true);
        
        static int selected_tab = 0;
        const char* tab_names[] = {"Botting", "Hacks", "Assists", "Render", "Settings", "Customization"};
        
        for (int i = 0; i < 6; i++) {
            if (ImGui::Selectable(tab_names[i], selected_tab == i, 0, ImVec2(120, 35))) {
                selected_tab = i;
            }
        }
        
        ImGui::EndChild();
        
        ImGui::SameLine();
        
        ImGui::BeginChild("ContentPanel", ImVec2(0, 0), true);
        
        switch (selected_tab) {
            case 0: 
            renderBottingTab();
            break;
            case 1: 
            renderHacksTab();
            break;
            case 2: 
            renderAssistsTab();
            break;
            case 3: 
            renderRenderTab();
            break;
            case 4: 
            renderSettingsTab();
            break;
            case 5: 
            renderCustomizationTab();
            break;
        }
        
        ImGui::EndChild(); 
        ImGui::EndChild(); 
    }
    ImGui::End();
}