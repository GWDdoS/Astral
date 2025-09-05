#include "../includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

// Add a variable to track the current tab
static int currentTab = 0;

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

    io.FontGlobalScale = 1.0f;
    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 4.0f;
    style.ChildRounding = 4.0f;
    style.ScaleAllSizes(1.0f);
    
    // Dark black color scheme instead of green
    ImVec4 baseDark = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);       // Dark black
    ImVec4 darkBaseDark = ImVec4(0.05f, 0.05f, 0.05f, 1.0f); // Darker black  
    ImVec4 lightBaseDark = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);   // Lighter black
    ImVec4 baseAccent = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);   // Medium black
    
    applyBackgroundTheme();
    
    // Apply dark black theme
    style.Colors[ImGuiCol_TitleBg] = darkBaseDark;
    style.Colors[ImGuiCol_TitleBgActive] = lightBaseDark;  // Lighter for active title
    style.Colors[ImGuiCol_Button] = baseDark;
    style.Colors[ImGuiCol_ButtonHovered] = lightBaseDark;
    style.Colors[ImGuiCol_ButtonActive] = baseAccent;
    style.Colors[ImGuiCol_FrameBgActive] = baseAccent;
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Light grey checkmark
    style.Colors[ImGuiCol_SliderGrab] = lightBaseDark;
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    style.Colors[ImGuiCol_Header] = baseDark;
    style.Colors[ImGuiCol_HeaderHovered] = lightBaseDark;
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    style.Colors[ImGuiCol_Tab] = baseDark;
    style.Colors[ImGuiCol_TabHovered] = lightBaseDark;
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = darkBaseDark;
    style.Colors[ImGuiCol_TabUnfocusedActive] = baseDark;
    
    styleApplied = true;
}

void renderBottingTab()
{
    ImGui::Text("Botting Features:");
    ImGui::Separator();
    
    if (ImGui::Button("Record Macro", ImVec2(150, 30))) {
        // Add macro recording functionality
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Play Macro", ImVec2(150, 30))) {
        // Add macro playback functionality
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
        // Add render functionality
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Stop Render", ImVec2(150, 30))) {
        // Add stop render functionality
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
    
    ImGui::Text("Color Theme:");
    if (styleApplied) {
        ImGui::ColorEdit3("Accent Color", themeColor);
    }
    
    ImGui::Spacing();
    ImGui::Text("Font Settings:");
    ImGui::SetNextItemWidth(120);
    ImGui::SliderInt("Font Type", &fontType, 0, 5);
    
    static float uiScale = 1.0f;
    ImGui::Text("UI Scale:");
    ImGui::SetNextItemWidth(150);
    if (ImGui::SliderFloat("##uiscale", &uiScale, 0.5f, 2.0f, "%.2f")) {
        ImGui::GetStyle().ScaleAllSizes(uiScale);
    }
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
        
        // Only apply custom colors if they're not the default dark theme
        if (themeColor[0] > 0.1f || themeColor[1] > 0.1f || themeColor[2] > 0.1f) {
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
    }
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    
    bool currentGuiState = ImGuiCocos::get().isVisible();
    if (currentGuiState != guiVisible) {
        guiVisible = currentGuiState;
    }
    
    // Increased window size
    ImGui::SetNextWindowSize(ImVec2(600, 450), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    
    if (ImGui::Begin("Astral Mod", nullptr, window_flags)) {
        
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        
        // Dark gradient that matches button colors
        ImU32 col_top = IM_COL32(25, 25, 25, 255);      // Lighter dark (matches button hover)
        ImU32 col_bottom = IM_COL32(13, 13, 13, 255);   // Darker (matches buttons)
        
        draw_list->AddRectFilledMultiColor(
            windowPos,
            ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
            col_top, col_top, col_bottom, col_bottom
        );
        
        // Tab buttons
        ImGui::Text("Categories:");
        
        const char* tabNames[] = {"Botting", "Hacks", "AutoClicker", "Render", "Settings", "Customization"};
        const int tabCount = 6;
        
        for (int i = 0; i < tabCount; i++) {
            if (i > 0) ImGui::SameLine();
            
            // Highlight active tab with very dark grey
            if (currentTab == i) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.05f, 0.05f, 0.05f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
            }
            
            if (ImGui::Button(tabNames[i], ImVec2(90, 25))) {
                currentTab = i;
            }
            
            if (currentTab == i) {
                ImGui::PopStyleColor(2);
            }
        }
        
        ImGui::Separator();
        ImGui::Spacing();
        
        // Render the appropriate tab content
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