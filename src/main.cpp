// Ok no we HAVE TO MOVE ALL THIS SHIT OUT OF HERE OMFG. Ill be remakign the whole code branch soon omfg. 

#include "includes.hpp"

using namespace geode::prelude;

/* de3am is a boykisser and a list helper
   Breuhh is also a boykisser and a list helper. (de3am told me to put this) 
*/

// The unholy list of vars
//bools
bool noclipP1Enabled = false;
bool noclipP2Enabled = false;
bool noclipEnabled = false;
bool recording = false;
bool replaying = false;
bool rendering = false;
bool trajectoryEnabled = false;
bool layoutEnabled = false;
bool oldphysEnabled = false;
bool styleApplied = false;
bool framestepEnabled = false;
bool lockedDeltaEnabled = false;
bool guiVisible = false;

//Floats
float seedValue = 1.0f;
float tpsValue = 240.0f;
float speedValue = 1.0f;
float themeColor[3] = {0.2f, 0.7f, 0.4f};  // Darker green default

//Ints
int selectedKeybind = 0; // idk how to do real custom keybinds
int backgroundTheme = 0;
int inputMerge = 0;

//Chars
char macroName[128] = "Test";

// dumbahh fix i actually haev to rework this, move to /keybinds.cpp
const char* keybindNames[] = {"Alt", "F1", "F2", "F3", "F4", "F5", "Insert", "Home", "End"};
cocos2d::enumKeyCodes keybindCodes[] = {
    cocos2d::enumKeyCodes::KEY_Alt,
    cocos2d::enumKeyCodes::KEY_F1,
    cocos2d::enumKeyCodes::KEY_F2,
    cocos2d::enumKeyCodes::KEY_F3,
    cocos2d::enumKeyCodes::KEY_F4,
    cocos2d::enumKeyCodes::KEY_F5,
    cocos2d::enumKeyCodes::KEY_Insert,
    cocos2d::enumKeyCodes::KEY_Home,
    cocos2d::enumKeyCodes::KEY_End
};

const char* backgroundThemeNames[] = {"Dark", "Light", "Medium"};

#ifdef GEODE_IS_WINDOWS
#include <windows.h>

void setCursorVisibility(bool visible) {
    static bool lastState = true;
    static int cursorCount = 0;
    
    if (visible != lastState) {
        if (visible) {
            // Show cursor - keep calling ShowCursor(TRUE) until cursor is visible
            while (ShowCursor(TRUE) < 0) {
                // Continue until cursor count is >= 0 (visible)
            }
        } else {
            // Hide cursor - keep calling ShowCursor(FALSE) until cursor is hidden
            while (ShowCursor(FALSE) >= 0) {
                // Continue until cursor count is < 0 (hidden)
            }
        }
        lastState = visible;
    }
}
#endif

void applyBackgroundTheme() {
    auto& style = ImGui::GetStyle();
    
    switch(backgroundTheme) {
        case 0: // Dark
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.75f);  // 75% opacity
            style.Colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.75f);   // 75% opacity
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.8f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.18f, 0.18f, 0.8f);
            style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
            break;
        case 1: // Light
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.75f);  // 75% opacity
            style.Colors[ImGuiCol_ChildBg] = ImVec4(0.96f, 0.96f, 0.96f, 0.75f);   // 75% opacity
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.94f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.9f, 0.9f, 0.9f, 0.8f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.85f, 0.85f, 0.85f, 0.8f);
            style.Colors[ImGuiCol_Text] = ImVec4(0.05f, 0.05f, 0.05f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
            break;
        case 2: // Medium
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.3f, 0.3f, 0.3f, 0.75f);     // 75% opacity
            style.Colors[ImGuiCol_ChildBg] = ImVec4(0.35f, 0.35f, 0.35f, 0.75f);   // 75% opacity
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.3f, 0.3f, 0.3f, 0.94f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.45f, 0.45f, 0.45f, 0.8f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.55f, 0.55f, 0.55f, 0.8f);
            style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
            break;
    }
}

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        auto& style = ImGui::GetStyle();
        auto& io = ImGui::GetIO();
        
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
   }).draw([] {
        
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
        
        // Window flags: no title bar, no close button, no collapse, no resize
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        
        // Update GUI visibility state and cursor
        bool currentGuiState = ImGuiCocos::get().isVisible();
        if (currentGuiState != guiVisible) {
            guiVisible = currentGuiState;
#ifdef GEODE_IS_WINDOWS
            setCursorVisibility(guiVisible);
#endif
        }
        
        // Set window size and position
        ImGui::SetNextWindowSize(ImVec2(600, 450), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
        
        if (ImGui::Begin("Astral Mod", nullptr, window_flags)) {
            // Custom title bar with centered text
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImVec2 windowPos = ImGui::GetWindowPos();
            
            // Draw larger banner area
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            ImVec2 banner_min = windowPos;
            ImVec2 banner_max = ImVec2(windowPos.x + windowSize.x, windowPos.y + 50);
            
            // Banner background with theme color
            ImVec4 bannerColor = ImVec4(themeColor[0], themeColor[1], themeColor[2], 0.8f);
            draw_list->AddRectFilled(banner_min, banner_max, ImGui::ColorConvertFloat4ToU32(bannerColor), 12.0f, ImDrawFlags_RoundCornersTop);
            
            // Center the "Astral: Bot" text in the banner
            const char* title = "Astral: Bot";
            ImVec2 text_size = ImGui::CalcTextSize(title);
            ImVec2 text_pos = ImVec2(
                windowPos.x + (windowSize.x - text_size.x) * 0.5f,
                windowPos.y + (50 - text_size.y) * 0.5f
            );
            
            draw_list->AddText(text_pos, IM_COL32(255, 255, 255, 255), title);
            
            // Add spacing for the banner
            ImGui::Dummy(ImVec2(0, 50));
            
            // Main content area with side tabs
            ImGui::BeginChild("MainContent", ImVec2(0, -5), false, ImGuiWindowFlags_NoScrollbar);
            
            // Create horizontal layout: tabs on left, content on right
            ImGui::BeginChild("TabsPanel", ImVec2(140, 0), true);
            
            static int selected_tab = 0;
            const char* tab_names[] = {"Botting", "Hacks", "Assists", "Render", "Settings", "Custom"};
            
            for (int i = 0; i < 6; i++) {
                if (ImGui::Selectable(tab_names[i], selected_tab == i, 0, ImVec2(120, 35))) {
                    selected_tab = i;
                }
            }
            
            ImGui::EndChild();
            
            ImGui::SameLine();
            
            // Content area
            ImGui::BeginChild("ContentPanel", ImVec2(0, 0), true);
            
            switch (selected_tab) {
                case 0: // Botting
                    ImGui::Separator();
                    ImGui::InputText("Macro Name", macroName, sizeof(macroName));
                    if (ImGui::Button("Record Macro", ImVec2(120, 0))) {
                        
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Save Macro", ImVec2(120, 0))) {
                        
                    }
                    
                    ImGui::Spacing();
                    ImGui::Text("TPS Bypass:");
                    ImGui::SetNextItemWidth(200);
                    ImGui::InputFloat("TPS", &tpsValue);
                    
                    ImGui::Checkbox("Lock Delta Time", &lockedDeltaEnabled);
                    
                    ImGui::Separator();
                    ImGui::SetNextItemWidth(200);
                    ImGui::InputFloat("Speedhack", &speedValue);  
                    ImGui::Checkbox("Enable Trajectory", &trajectoryEnabled);
                    
                    ImGui::Checkbox("Frame Stepper", &framestepEnabled);
    
                    if (ImGui::Button("Step Frame", ImVec2(120, 0))) {
                    }

                    ImGui::Checkbox("Enable 2.1 Legacy Physics", &oldphysEnabled);
                    break;
                    
                case 1: // Hacks
                    ImGui::Separator();
                    ImGui::Checkbox("Enable Noclip (Both Players)", &noclipEnabled);
                    
                    ImGui::Separator();
                    ImGui::Text("Individual Player Noclip:");
                    ImGui::Checkbox("Player 1 Noclip", &noclipP1Enabled);
                    ImGui::Checkbox("Player 2 Noclip", &noclipP2Enabled);
                    
                    ImGui::Separator();
                    ImGui::Checkbox("Show Layout", &layoutEnabled);
                    ImGui::SetNextItemWidth(200);
                    ImGui::InputFloat("Lock Seed", &seedValue);
                    break;
                    
                case 2: // Assists
                    ImGui::Separator();
                    if (ImGui::Button("Start AutoClicker", ImVec2(140, 0))) {
                    }
                    if (ImGui::Button("Stop AutoClicker", ImVec2(140, 0))) {
                    }
                    if (ImGui::Button("Dual Merge Input", ImVec2(140, 0))) {
                    }
                    ImGui::SetNextItemWidth(200);
                    ImGui::Combo("Input Type", &inputMerge, "Input\0Space\0Up\0Left\0Right\0");
                    break;
                    
                case 3: // Render
                    ImGui::Separator();
                    if (ImGui::Button("Start Render", ImVec2(120, 0))) {
                    }
                    if (ImGui::Button("Stop Render", ImVec2(120, 0))) {
                    }
                    break;
                    
                case 4: // Settings
                    ImGui::Separator();
                    ImGui::Text("GUI Settings:");
                    ImGui::Separator();
                    
                    ImGui::Text("Toggle GUI Key:");
                    ImGui::SetNextItemWidth(200);
                    if (ImGui::Combo("##keybind", &selectedKeybind, keybindNames, IM_ARRAYSIZE(keybindNames))) {
                    }
                    
                    ImGui::Text("Current Key: %s", keybindNames[selectedKeybind]);
                    
                    ImGui::Separator();
                    ImGui::Text("Background Theme:");
                    ImGui::SetNextItemWidth(200);
                    if (ImGui::Combo("##backgroundtheme", &backgroundTheme, backgroundThemeNames, IM_ARRAYSIZE(backgroundThemeNames))) {
                        applyBackgroundTheme();
                    }
                    
                    ImGui::Separator();
                    ImGui::Text("Theme Color:");
                    if (ImGui::ColorEdit3("##themecolor", themeColor)) {
                    }
                    
                    if (ImGui::Button("Reset to Default", ImVec2(150, 0))) {
                        themeColor[0] = 0.2f; // R
                        themeColor[1] = 0.7f; // G  
                        themeColor[2] = 0.4f; // B
                    }
                    break;
                    
                case 5: // Customization
                    ImGui::Separator();
                    ImGui::Text("More to come soon :)");
                    break;
            }
            
            ImGui::EndChild(); // ContentPanel
            ImGui::EndChild(); // MainContent
        }
        ImGui::End();
    });
}

#ifdef GEODE_IS_WINDOWS
class $modify(ImGuiKeybindHook, cocos2d::CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        if (selectedKeybind >= 0 && selectedKeybind < IM_ARRAYSIZE(keybindCodes)) {
            if (key == keybindCodes[selectedKeybind] && isKeyDown) {
                ImGuiCocos::get().toggle();
                // Update cursor visibility when toggling
                guiVisible = ImGuiCocos::get().isVisible();
                setCursorVisibility(guiVisible);
            }
        }
        return cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};
#else
// Non-Windows platforms - no cursor management
class $modify(ImGuiKeybindHook, cocos2d::CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        if (selectedKeybind >= 0 && selectedKeybind < IM_ARRAYSIZE(keybindCodes)) {
            if (key == keybindCodes[selectedKeybind] && isKeyDown) {
                ImGuiCocos::get().toggle();
            }
        }
        return cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};
#endif