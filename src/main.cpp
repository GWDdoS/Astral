// Ok no we HAVE TO MOVE ALL THIS SHIT OUT OF HERE OMFG. Ill be remakign the whole code branch soon omfg.

#include "includes.hpp"

using namespace geode::prelude;

/*
de3am is a boykisser and a list helper
Breuhh is also a boykisser and a list helper. (de3am told me to put this)
*/

// The unholy list of vars
// bools
bool noclipP1 = false;
bool noclipP2 = false;
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
bool speedhackEnabled = false;
bool speedhackAudio = false;

// Keybind capture variables
bool isCapturingKeybind = false;
cocos2d::enumKeyCodes capturedCustomKey = cocos2d::enumKeyCodes::KEY_Alt; // Default to Alt

// Floats
float seedValue = 1.0f;
float tpsValue = 240.0f;
float speedValue = 1.0f;
float themeColor[3] = {0.2f, 0.7f, 0.4f}; // Darker green default
float currentPitch = 1.0f;
float currentSpeedValue = 1.0f;

// Ints
int backgroundTheme = 0;
int inputMerge = 0;
int noclipMode = 0;

// Chars
char macroName[128] = "Test";

const char *backgroundThemeNames[] = {"Dark", "Light", "Medium"};
// Ai is good for one thing, making a fucking massive list :skull:
const char* getKeyName(cocos2d::enumKeyCodes keyCode) {
    switch(keyCode) {
        case cocos2d::enumKeyCodes::KEY_Alt: return "Alt";
        case cocos2d::enumKeyCodes::KEY_F1: return "F1";
        case cocos2d::enumKeyCodes::KEY_F2: return "F2";
        case cocos2d::enumKeyCodes::KEY_F3: return "F3";
        case cocos2d::enumKeyCodes::KEY_F4: return "F4";
        case cocos2d::enumKeyCodes::KEY_F5: return "F5";
        case cocos2d::enumKeyCodes::KEY_F6: return "F6";
        case cocos2d::enumKeyCodes::KEY_F7: return "F7";
        case cocos2d::enumKeyCodes::KEY_F8: return "F8";
        case cocos2d::enumKeyCodes::KEY_F9: return "F9";
        case cocos2d::enumKeyCodes::KEY_F10: return "F10";
        case cocos2d::enumKeyCodes::KEY_F11: return "F11";
        case cocos2d::enumKeyCodes::KEY_F12: return "F12";
        case cocos2d::enumKeyCodes::KEY_Insert: return "Insert";
        case cocos2d::enumKeyCodes::KEY_Home: return "Home";
        case cocos2d::enumKeyCodes::KEY_End: return "End";
        case cocos2d::enumKeyCodes::KEY_PageUp: return "Page Up";
        case cocos2d::enumKeyCodes::KEY_PageDown: return "Page Down";
        case cocos2d::enumKeyCodes::KEY_Delete: return "Delete";
        case cocos2d::enumKeyCodes::KEY_Space: return "Space";
        case cocos2d::enumKeyCodes::KEY_Enter: return "Enter";
        case cocos2d::enumKeyCodes::KEY_Escape: return "Escape";
        case cocos2d::enumKeyCodes::KEY_Tab: return "Tab";
        case cocos2d::enumKeyCodes::KEY_Shift: return "Shift";
        case cocos2d::enumKeyCodes::KEY_Control: return "Ctrl";
        case cocos2d::enumKeyCodes::KEY_ArrowLeft: return "Left Arrow";
        case cocos2d::enumKeyCodes::KEY_ArrowRight: return "Right Arrow";
        case cocos2d::enumKeyCodes::KEY_ArrowUp: return "Up Arrow";
        case cocos2d::enumKeyCodes::KEY_ArrowDown: return "Down Arrow";
        
        // Missing cases to add:
        case cocos2d::enumKeyCodes::KEY_None: return "None";
        case cocos2d::enumKeyCodes::KEY_Backspace: return "Backspace";
        case cocos2d::enumKeyCodes::KEY_Pause: return "Pause";
        case cocos2d::enumKeyCodes::KEY_CapsLock: return "Caps Lock";
        case cocos2d::enumKeyCodes::KEY_Select: return "Select";
        
        // Number keys (0-9)
        /* these dont work
        case cocos2d::enumKeyCodes::KEY_0: return "0";
        case cocos2d::enumKeyCodes::KEY_1: return "1";
        case cocos2d::enumKeyCodes::KEY_2: return "2";
        case cocos2d::enumKeyCodes::KEY_3: return "3";
        case cocos2d::enumKeyCodes::KEY_4: return "4";
        case cocos2d::enumKeyCodes::KEY_5: return "5";
        case cocos2d::enumKeyCodes::KEY_6: return "6";
        case cocos2d::enumKeyCodes::KEY_7: return "7";
        case cocos2d::enumKeyCodes::KEY_8: return "8";
        case cocos2d::enumKeyCodes::KEY_9: return "9";
        */
        // Letter keys (A-Z)
        case cocos2d::enumKeyCodes::KEY_A: return "A";
        case cocos2d::enumKeyCodes::KEY_B: return "B";
        case cocos2d::enumKeyCodes::KEY_C: return "C";
        case cocos2d::enumKeyCodes::KEY_D: return "D";
        case cocos2d::enumKeyCodes::KEY_E: return "E";
        case cocos2d::enumKeyCodes::KEY_F: return "F";
        case cocos2d::enumKeyCodes::KEY_G: return "G";
        case cocos2d::enumKeyCodes::KEY_H: return "H";
        case cocos2d::enumKeyCodes::KEY_I: return "I";
        case cocos2d::enumKeyCodes::KEY_J: return "J";
        case cocos2d::enumKeyCodes::KEY_K: return "K";
        case cocos2d::enumKeyCodes::KEY_L: return "L";
        case cocos2d::enumKeyCodes::KEY_M: return "M";
        case cocos2d::enumKeyCodes::KEY_N: return "N";
        case cocos2d::enumKeyCodes::KEY_O: return "O";
        case cocos2d::enumKeyCodes::KEY_P: return "P";
        case cocos2d::enumKeyCodes::KEY_Q: return "Q";
        case cocos2d::enumKeyCodes::KEY_R: return "R";
        case cocos2d::enumKeyCodes::KEY_S: return "S";
        case cocos2d::enumKeyCodes::KEY_T: return "T";
        case cocos2d::enumKeyCodes::KEY_U: return "U";
        case cocos2d::enumKeyCodes::KEY_V: return "V";
        case cocos2d::enumKeyCodes::KEY_W: return "W";
        case cocos2d::enumKeyCodes::KEY_X: return "X";
        case cocos2d::enumKeyCodes::KEY_Y: return "Y";
        case cocos2d::enumKeyCodes::KEY_Z: return "Z";
        
        // Numeric keypad keys
        /* these dont work
        case cocos2d::enumKeyCodes::KEY_Num0: return "Numpad 0";
        case cocos2d::enumKeyCodes::KEY_Num1: return "Numpad 1";
        case cocos2d::enumKeyCodes::KEY_Num2: return "Numpad 2";
        case cocos2d::enumKeyCodes::KEY_Num3: return "Numpad 3";
        case cocos2d::enumKeyCodes::KEY_Num4: return "Numpad 4";
        case cocos2d::enumKeyCodes::KEY_Num5: return "Numpad 5";
        case cocos2d::enumKeyCodes::KEY_Num6: return "Numpad 6";
        case cocos2d::enumKeyCodes::KEY_Num7: return "Numpad 7";
        case cocos2d::enumKeyCodes::KEY_Num8: return "Numpad 8";
        case cocos2d::enumKeyCodes::KEY_Num9: return "Numpad 9";
        
        case cocos2d::enumKeyCodes::KEY_NumMultiply: return "Numpad *";
        case cocos2d::enumKeyCodes::KEY_NumPlus: return "Numpad +";
        case cocos2d::enumKeyCodes::KEY_NumMinus: return "Numpad -";
        case cocos2d::enumKeyCodes::KEY_NumDelete: return "Numpad Delete";
        case cocos2d::enumKeyCodes::KEY_NumDivide: return "Numpad /";
        */
        
        // Lock keys
        /* these dont work
        case cocos2d::enumKeyCodes::KEY_NumLock: return "Num Lock";
        */
        case cocos2d::enumKeyCodes::KEY_ScrollLock: return "Scroll Lock";
        
        // Punctuation and special characters
        /* these dont work
        case cocos2d::enumKeyCodes::KEY_Semicolon: return ";";
        case cocos2d::enumKeyCodes::KEY_Equal: return "=";
        case cocos2d::enumKeyCodes::KEY_Comma: return ",";
        case cocos2d::enumKeyCodes::KEY_Dash: return "-";
        case cocos2d::enumKeyCodes::KEY_Period: return ".";
        case cocos2d::enumKeyCodes::KEY_ForwardSlash: return "/";
        case cocos2d::enumKeyCodes::KEY_Grave: return "`";
        case cocos2d::enumKeyCodes::KEY_OpenBracket: return "[";
        case cocos2d::enumKeyCodes::KEY_Backslash: return "\\";
        case cocos2d::enumKeyCodes::KEY_CloseBracket: return "]";
        case cocos2d::enumKeyCodes::KEY_Quote: return "'";
        */
        
        // D-pad keys (for gamepad/controller support)
        /* these dont work
        case cocos2d::enumKeyCodes::KEY_DpadLeft: return "D-pad Left";
        case cocos2d::enumKeyCodes::KEY_DpadRight: return "D-pad Right";
        case cocos2d::enumKeyCodes::KEY_DpadUp: return "D-pad Up";
        case cocos2d::enumKeyCodes::KEY_DpadDown: return "D-pad Down";
        case cocos2d::enumKeyCodes::KEY_DpadCenter: return "D-pad Center";
        */
        default: return "Unknown Key";
    }
}

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

$on_mod(Loaded)
{
    ImGuiCocos::get().setup([]
        {
            auto& style = ImGui::GetStyle();
            auto& io = ImGui::GetIO();
            auto* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((Mod::get()->getResourcesDir() / "font.ttf").string().c_str(), 16.0f);
            
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
            
            styleApplied = true; })
            .draw([]
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
                        ImVec2 banner_max = ImVec2(windowPos.x + windowSize.x, windowPos.y + 50);
                        
                        ImVec4 bannerColor = ImVec4(themeColor[0], themeColor[1], themeColor[2], 0.8f);
                        draw_list->AddRectFilled(banner_min, banner_max, ImGui::ColorConvertFloat4ToU32(bannerColor), 12.0f, ImDrawFlags_RoundCornersTop);
                        
                        const char* title = "Astral: Bot";
                        ImVec2 text_size = ImGui::CalcTextSize(title * 0.5f);
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
                            break;
                            
                            case 1: 
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
                            break;
                            
                            case 2: 
                            ImGui::Separator();
                            if (ImGui::Button("Start AutoClicker", ImVec2(140, 0))) {
                            }
                            if (ImGui::Button("Stop AutoClicker", ImVec2(140, 0))) {
                            }
                            if (ImGui::Button("Dual Merge Input", ImVec2(140, 0))) {
                            }
                            ImGui::SetNextItemWidth(150);
                            ImGui::Combo("Input Type", &inputMerge, "Input\0Space\0Up\0Left\0Right\0");
                            break;
                            
                            case 3: 
                            ImGui::Separator();
                            if (ImGui::Button("Start Render", ImVec2(120, 0))) {
                            }
                            if (ImGui::Button("Stop Render", ImVec2(120, 0))) {
                            }
                            break;
                            
                            case 4: 
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
                                
                                ImGui::Separator();
                                ImGui::Text("Background Theme:");
                                ImGui::SetNextItemWidth(150);
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
                            }
                            
                            case 5: 
                            ImGui::Separator();
                            ImGui::Text("More to come soon :)");
                            break;
                        }
                        
                        ImGui::EndChild(); 
                        ImGui::EndChild(); 
                    }
                    ImGui::End(); });
                }
                // i should learn how to actually do this later
                class $modify(ImGuiKeybindHook, cocos2d::CCKeyboardDispatcher){
                    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat)
                    {
                        if (isCapturingKeybind && isKeyDown && !isKeyRepeat) {
                            if (key == cocos2d::enumKeyCodes::KEY_Escape) {
                                isCapturingKeybind = false;
                            } else {
                                capturedCustomKey = key;
                                isCapturingKeybind = false;
                            }
                            return true; 
                        }
                        
                        if (capturedCustomKey != cocos2d::enumKeyCodes::KEY_None && key == capturedCustomKey && isKeyDown) {
                            ImGuiCocos::get().toggle();
                            guiVisible = ImGuiCocos::get().isVisible();
                        }
                        
                        return cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
                    }
                };