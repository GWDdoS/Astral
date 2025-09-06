#include "../includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

static int currentTab = 0;

void applyBackgroundTheme()
{
    auto &style = ImGui::GetStyle();
    
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.9f);    
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.9f);      
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.95f);     
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.9f);   
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1f, 0.1f, 0.1f, 0.9f); 
    style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);      
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); 
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
    
    ImVec4 pureBlack = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);          
    ImVec4 veryDarkGrey = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);    
    ImVec4 darkGrey = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);           
    ImVec4 mediumGrey = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);      
    
    applyBackgroundTheme();
    
    style.Colors[ImGuiCol_TitleBg] = pureBlack;
    style.Colors[ImGuiCol_TitleBgActive] = veryDarkGrey;
    style.Colors[ImGuiCol_Button] = pureBlack;
    style.Colors[ImGuiCol_ButtonHovered] = veryDarkGrey;
    style.Colors[ImGuiCol_ButtonActive] = darkGrey;
    style.Colors[ImGuiCol_FrameBgActive] = darkGrey;
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); 
    style.Colors[ImGuiCol_SliderGrab] = veryDarkGrey;
    style.Colors[ImGuiCol_SliderGrabActive] = darkGrey;
    style.Colors[ImGuiCol_Header] = pureBlack;
    style.Colors[ImGuiCol_HeaderHovered] = veryDarkGrey;
    style.Colors[ImGuiCol_HeaderActive] = darkGrey;
    style.Colors[ImGuiCol_Tab] = pureBlack;
    style.Colors[ImGuiCol_TabHovered] = veryDarkGrey;
    style.Colors[ImGuiCol_TabActive] = darkGrey;
    style.Colors[ImGuiCol_TabUnfocused] = pureBlack;
    style.Colors[ImGuiCol_TabUnfocusedActive] = veryDarkGrey;
    
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
    
    ImGui::Text("Accent Color:");
    ImGui::ColorEdit3("##accentcolor", themeColor);
}

void renderMainGui()
{
    if (styleApplied) {
        auto& style = ImGui::GetStyle();
        ImVec4 customColor = ImVec4(themeColor[0], themeColor[1], themeColor[2], 1.0f);
        ImVec4 customColorDark = ImVec4(themeColor[0] * 0.6f, themeColor[1] * 0.6f, themeColor[2] * 0.6f, 1.0f); 
        ImVec4 customColorLight = ImVec4(
            std::min(1.0f, themeColor[0] + 0.1f), 
            std::min(1.0f, themeColor[1] + 0.1f), 
            std::min(1.0f, themeColor[2] + 0.1f), 
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
    
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    
    if (ImGui::Begin("Astral Mod", nullptr, window_flags)) {
        
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        
        ImVec4 topColor = ImVec4(
            std::max(0.0f, themeColor[0] - 0.1f), 
            std::max(0.0f, themeColor[1] - 0.1f), 
            std::max(0.0f, themeColor[2] - 0.1f), 
            1.0f
        );
        ImVec4 bottomColor = ImVec4(
            std::min(1.0f, themeColor[0] + 0.1f), 
            std::min(1.0f, themeColor[1] + 0.1f), 
            std::min(1.0f, themeColor[2] + 0.1f), 
            1.0f
        );
        
        ImU32 col_top = IM_COL32(
            (int)(topColor.x * 255), 
            (int)(topColor.y * 255), 
            (int)(topColor.z * 255), 
            255
        );
        ImU32 col_bottom = IM_COL32(
            (int)(bottomColor.x * 255), 
            (int)(bottomColor.y * 255), 
            (int)(bottomColor.z * 255), 
            255
        );
        
        draw_list->AddRectFilledMultiColor(
            windowPos,
            ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
            col_top, col_top, col_bottom, col_bottom
        );
        
        ImGui::Text("Categories:");
        
        const char* tabNames[] = {"Botting", "Hacks", "AutoClicker", "Render", "Settings", "Customization"};
        const int tabCount = 6;
        
        for (int i = 0; i < tabCount; i++) {
            if (i > 0) ImGui::SameLine();
            
            if (currentTab == i) {
                ImVec4 activeTabColor = ImVec4(
                    std::min(1.0f, themeColor[0] + 0.20f),
                    std::min(1.0f, themeColor[1] + 0.18f),
                    std::min(1.0f, themeColor[2] + 0.15f),
                    1.0f
                );
                ImVec4 activeTabHover = ImVec4(
                    std::min(1.0f, themeColor[0] + 0.25f),
                    std::min(1.0f, themeColor[1] + 0.23f),
                    std::min(1.0f, themeColor[2] + 0.20f),
                    1.0f
                );
                ImGui::PushStyleColor(ImGuiCol_Button, activeTabColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, activeTabHover);
            }
            
            if (ImGui::Button(tabNames[i], ImVec2(120, 30))) {
                currentTab = i;
            }
            
            if (currentTab == i) {
                ImGui::PopStyleColor(2);
            }
        }
        
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
    }
    ImGui::End();
}