// Ok no we HAVE TO MOVE ALL THIS SHIT OUT OF HERE OMFG. Ill be remakign the whole code branch soon omfg. 

#include "includes.hpp"

using namespace geode::prelude;

/* de3am is a boykisser and a list helper
   Breuhh is also a boykisser and a list helper. (de3am told me to put this) 
*/

// The unholy list of vars
//bools
bool noclipEnabled = false;
bool recording = false;
bool replaying = false;
bool rendering = false;
bool trajectoryEnabled = false;
bool layoutEnabled = false;
bool oldphysEnabled = false;
bool styleApplied = false;
bool framestepEnabled = false;
bool lockedDeltaEnabled = false; // NEW: Lock delta option

//Floats
float seedValue = 1.0f;
float tpsValue = 240.0f;
float speedValue = 1.0f;
float themeColor[3] = {0.4f, 1.0f, 0.7f};  // smt that might be close to echo

//Ints
int selectedTheme = 0;
int selectedKeybind = 0; // idk how to do real custom keybinds

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

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        auto& style = ImGui::GetStyle();
        auto& io = ImGui::GetIO();
        
        io.FontGlobalScale = 1.2f;
        style.WindowRounding = 12.0f;
        style.FrameRounding = 8.0f;
        style.PopupRounding = 8.0f;
        style.ScrollbarRounding = 8.0f;
        style.GrabRounding = 8.0f;
        style.TabRounding = 8.0f;
        style.ChildRounding = 8.0f;
        style.ScaleAllSizes(2.0f);
        // Was going to make different themes but ehhh
        ImVec4 baseGreen = ImVec4(0.4f, 1.0f, 0.7f, 1.0f);
        ImVec4 darkBaseGreen = ImVec4(0.3f, 0.8f, 0.55f, 1.0f);
        ImVec4 lightBaseGreen = ImVec4(0.5f, 1.0f, 0.8f, 1.0f);
        ImVec4 baseAccent = ImVec4(0.2f, 0.9f, 0.6f, 1.0f);
        // tldr removing 90% of this shit
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.9f);
        style.Colors[ImGuiCol_TitleBg] = darkBaseGreen;
        style.Colors[ImGuiCol_TitleBgActive] = baseGreen;
        style.Colors[ImGuiCol_Button] = darkBaseGreen;
        style.Colors[ImGuiCol_ButtonHovered] = baseGreen;
        style.Colors[ImGuiCol_ButtonActive] = baseAccent;
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.2f, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3f, 0.3f, 0.3f, 0.8f);
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
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.2f, 0.6f, 0.4f, 0.8f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = darkBaseGreen;
        
        styleApplied = true;
   }).draw([] {
        
        if (styleApplied) {
            auto& style = ImGui::GetStyle();
            ImVec4 customColor = ImVec4(themeColor[0], themeColor[1], themeColor[2], 1.0f);
            ImVec4 customColorDark = ImVec4(themeColor[0] * 0.7f, themeColor[1] * 0.8f, themeColor[2] * 0.8f, 1.0f);
            ImVec4 customColorLight = ImVec4(
                std::min(1.0f, themeColor[0] * 1.2f), 
                std::min(1.0f, themeColor[1] * 1.0f), 
                std::min(1.0f, themeColor[2] * 1.15f), 
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
        

        if (ImGui::Begin("Astral Mod", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Separator();
            
            if (ImGui::BeginTabBar("##tabs")) {
                if (ImGui::BeginTabItem("Botting")) {
                    ImGui::Separator();
                    if (ImGui::Button("Record Macro")) {
                        
                    }
                    if (ImGui::Button("Save Macro")) {
                        
                    }
                    
                    ImGui::Text("TPS Bypass:");
                    ImGui::InputFloat("TPS", &tpsValue);
                    

                    
                    ImGui::Checkbox("Lock Delta Time", &lockDeltaEnabled);
                    
                    ImGui::Separator();
                    ImGui::InputFloat("Speedhack", &speedValue);  
                    ImGui::Checkbox("Enable Trajectory", &trajectoryEnabled);
                    
                    ImGui::Checkbox("Frame Stepper", &framestepEnabled);
    
                    if (ImGui::Button("Step Frame")) {
                    }

                    ImGui::Checkbox("Enable 2.1 Legacy Physics", &oldphysEnabled);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Hacks")) {
                    ImGui::Separator();
                    ImGui::Checkbox("Enable Noclip", &noclipEnabled);
                    ImGui::Checkbox("Show Layout", &layoutEnabled);
                    ImGui::InputFloat("Lock Seed", &seedValue);
                    
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("AutoClicker")) {
                    ImGui::Separator();
                    if (ImGui::Button("Start AutoClicker")) {
                    }
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Render")) {
                    ImGui::Separator();
                    if (ImGui::Button("Start Render")) {
                    }
                    if (ImGui::Button("Stop Render")) {
                    }
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Settings")) {
                    ImGui::Separator();
                    ImGui::Text("GUI Settings:");
                    ImGui::Separator();
                    
                    ImGui::Text("Toggle GUI Key:");
                    if (ImGui::Combo("##keybind", &selectedKeybind, keybindNames, IM_ARRAYSIZE(keybindNames))) {
                    }
                    
                    ImGui::Text("Current Key: %s", keybindNames[selectedKeybind]);
                    
                    ImGui::Separator();
                    ImGui::Text("Theme Color:");
                    if (ImGui::ColorEdit3("##themecolor", themeColor)) {
                    }
                    
                    if (ImGui::Button("Reset to Default")) {
                        themeColor[0] = 0.4f; // R
                        themeColor[1] = 1.0f; // G  
                        themeColor[2] = 0.7f; // B
                    }
                    
                    ImGui::Separator();
                    ImGui::Text("Other Settings:");
                    ImGui::Combo("Theme Style", &selectedTheme, "Custom Color\0Dark\0Light\0Classic\0");
                    
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    });
}

#ifndef GEODE_IS_IOS
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


/* Generated with AI, I have no clue if all these work :D

// Basic Text and Labels
ImGui::Text("Basic text");
ImGui::TextColored(ImVec4(1,0,0,1), "Colored text");
ImGui::TextWrapped("Wrapped text that spans multiple lines");
ImGui::TextDisabled("Disabled/grayed text");
ImGui::LabelText("Label", "Value");
ImGui::BulletText("Bullet point text");

// Buttons
ImGui::Button("Basic Button");
ImGui::SmallButton("Small Button");
ImGui::InvisibleButton("invisible", ImVec2(100, 20));
ImGui::ArrowButton("arrow", ImGuiDir_Left);
ImGui::ImageButton("image_btn", textureID, ImVec2(32, 32));

// Checkboxes and Radio Buttons
ImGui::Checkbox("Checkbox", &boolValue);
ImGui::CheckboxFlags("Flags", &flags, flagValue);
ImGui::RadioButton("Radio A", &radioValue, 0);
ImGui::RadioButton("Radio B", &radioValue, 1);

// Sliders
ImGui::SliderFloat("Float", &floatValue, 0.0f, 1.0f);
ImGui::SliderFloat2("Float2", float2Array, 0.0f, 1.0f);
ImGui::SliderFloat3("Float3", float3Array, 0.0f, 1.0f);
ImGui::SliderFloat4("Float4", float4Array, 0.0f, 1.0f);
ImGui::SliderInt("Int", &intValue, 0, 100);
ImGui::SliderInt2("Int2", int2Array, 0, 100);
ImGui::SliderInt3("Int3", int3Array, 0, 100);
ImGui::SliderInt4("Int4", int4Array, 0, 100);
ImGui::VSliderFloat("VSlider", ImVec2(20, 100), &floatValue, 0.0f, 1.0f);
ImGui::SliderAngle("Angle", &angleValue);

// Drag Controls
ImGui::DragFloat("Drag Float", &floatValue);
ImGui::DragFloat2("Drag Float2", float2Array);
ImGui::DragFloat3("Drag Float3", float3Array);
ImGui::DragFloat4("Drag Float4", float4Array);
ImGui::DragInt("Drag Int", &intValue);
ImGui::DragInt2("Drag Int2", int2Array);
ImGui::DragInt3("Drag Int3", int3Array);
ImGui::DragInt4("Drag Int4", int4Array);
ImGui::DragFloatRange2("Range", &minValue, &maxValue);

// Input Fields
ImGui::InputText("Text Input", buffer, sizeof(buffer));
ImGui::InputTextMultiline("Multiline", buffer, sizeof(buffer));
ImGui::InputTextWithHint("Hint", "Enter text here", buffer, sizeof(buffer));
ImGui::InputFloat("Float Input", &floatValue);
ImGui::InputFloat2("Float2 Input", float2Array);
ImGui::InputFloat3("Float3 Input", float3Array);
ImGui::InputFloat4("Float4 Input", float4Array);
ImGui::InputInt("Int Input", &intValue);
ImGui::InputInt2("Int2 Input", int2Array);
ImGui::InputInt3("Int3 Input", int3Array);
ImGui::InputInt4("Int4 Input", int4Array);
ImGui::InputDouble("Double Input", &doubleValue);

// Color Controls
ImGui::ColorEdit3("Color RGB", colorArray);
ImGui::ColorEdit4("Color RGBA", colorArray);
ImGui::ColorPicker3("Color Picker RGB", colorArray);
ImGui::ColorPicker4("Color Picker RGBA", colorArray);
ImGui::ColorButton("Color Button", ImVec4(1,0,0,1));

// Trees and Collapsing Headers
ImGui::TreeNode("Tree Node");
ImGui::TreeNodeEx("Tree Node Extended", ImGuiTreeNodeFlags_DefaultOpen);
ImGui::CollapsingHeader("Collapsing Header");
ImGui::SetNextItemOpen(true, ImGuiCond_Once);

// Selectables and Lists
ImGui::Selectable("Selectable", &selected);
ImGui::Selectable("Selectable with size", &selected, 0, ImVec2(100, 20));
ImGui::ListBox("ListBox", &currentItem, items, itemCount);
ImGui::ListBoxHeader("ListBox Header");
ImGui::ListBoxFooter();

// Combo Boxes
ImGui::Combo("Combo", &currentItem, items, itemCount);
ImGui::BeginCombo("Begin Combo", currentItemText);
ImGui::EndCombo();

// Menus
ImGui::BeginMenuBar();
ImGui::EndMenuBar();
ImGui::BeginMainMenuBar();
ImGui::EndMainMenuBar();
ImGui::BeginMenu("Menu");
ImGui::EndMenu();
ImGui::MenuItem("Menu Item", "Ctrl+M", &selected);
ImGui::MenuItem("Menu Item", "Ctrl+M", selected, enabled);

// Tooltips
ImGui::BeginTooltip();
ImGui::EndTooltip();
ImGui::SetTooltip("Tooltip text");

// Popups and Modals
ImGui::OpenPopup("PopupID");
ImGui::BeginPopup("PopupID");
ImGui::EndPopup();
ImGui::BeginPopupModal("Modal", &open);
ImGui::EndPopup();
ImGui::BeginPopupContextItem("Context");
ImGui::BeginPopupContextWindow("Window Context");
ImGui::BeginPopupContextVoid("Void Context");
ImGui::CloseCurrentPopup();

// Windows
ImGui::Begin("Window Title", &open);
ImGui::End();
ImGui::BeginChild("Child", ImVec2(200, 100));
ImGui::EndChild();

// Tabs
ImGui::BeginTabBar("TabBar");
ImGui::EndTabBar();
ImGui::BeginTabItem("Tab", &open);
ImGui::EndTabItem();
ImGui::SetTabItemClosed("TabToClose");

// Tables (ImGui 1.80+)
ImGui::BeginTable("Table", 3);
ImGui::EndTable();
ImGui::TableNextRow();
ImGui::TableNextColumn();
ImGui::TableSetupColumn("Column");
ImGui::TableHeadersRow();

// Layout and Spacing
ImGui::Separator();
ImGui::SameLine();
ImGui::NewLine();
ImGui::Spacing();
ImGui::Dummy(ImVec2(100, 50));
ImGui::Indent();
ImGui::Unindent();
ImGui::BeginGroup();
ImGui::EndGroup();

// Scrolling
ImGui::SetScrollX(scrollX);
ImGui::SetScrollY(scrollY);
ImGui::SetScrollHereX();
ImGui::SetScrollHereY();
ImGui::SetScrollFromPosX(posX);
ImGui::SetScrollFromPosY(posY);

// Focus and Activation
ImGui::SetItemDefaultFocus();
ImGui::SetKeyboardFocusHere();
ImGui::IsItemHovered();
ImGui::IsItemActive();
ImGui::IsItemFocused();
ImGui::IsItemClicked();
ImGui::IsItemVisible();
ImGui::IsItemEdited();
ImGui::IsItemActivated();
ImGui::IsItemDeactivated();
ImGui::IsItemDeactivatedAfterEdit();

// Mouse and Keyboard
ImGui::IsMouseClicked(ImGuiMouseButton_Left);
ImGui::IsMouseReleased(ImGuiMouseButton_Left);
ImGui::IsMouseDragging(ImGuiMouseButton_Left);
ImGui::IsKeyPressed(ImGuiKey_Space);
ImGui::IsKeyReleased(ImGuiKey_Space);
ImGui::GetMousePos();
ImGui::GetMouseDragDelta();

// Drawing and Graphics
ImDrawList* drawList = ImGui::GetWindowDrawList();
drawList->AddLine(ImVec2(0,0), ImVec2(100,100), IM_COL32(255,0,0,255));
drawList->AddRect(ImVec2(10,10), ImVec2(50,50), IM_COL32(255,255,255,255));
drawList->AddCircle(ImVec2(50,50), 20, IM_COL32(0,255,0,255));
drawList->AddText(ImVec2(10,10), IM_COL32(255,255,255,255), "Text");
ImGui::GetBackgroundDrawList();
ImGui::GetForegroundDrawList();

// Progress Bars
ImGui::ProgressBar(progress, ImVec2(200, 0));
ImGui::ProgressBar(progress, ImVec2(200, 0), "Progress");

// Plot Functions (if available)
ImGui::PlotLines("Lines", values, valueCount);
ImGui::PlotHistogram("Histogram", values, valueCount);

// Style and Theming
ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1,0,0,1));
ImGui::PopStyleColor();
ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.5f);
ImGui::PopStyleVar();
ImGui::PushFont(font);
ImGui::PopFont();
ImGui::PushID(id);
ImGui::PopID();
ImGui::PushItemWidth(width);
ImGui::PopItemWidth();
ImGui::PushTextWrapPos(wrapPos);
ImGui::PopTextWrapPos();

// Miscellaneous Utilities
ImGui::GetIO();
ImGui::GetStyle();
ImGui::GetVersion();
ImGui::GetTime();
ImGui::GetFrameCount();
ImGui::CalcTextSize("Text");
ImGui::CalcItemWidth();
ImGui::GetContentRegionAvail();
ImGui::GetContentRegionMax();
ImGui::GetWindowContentRegionMin();
ImGui::GetWindowContentRegionMax();
ImGui::GetCursorPos();
ImGui::SetCursorPos(ImVec2(x, y));
ImGui::GetCursorScreenPos();
ImGui::SetCursorScreenPos(ImVec2(x, y));
ImGui::AlignTextToFramePadding();

// Clipping
ImGui::PushClipRect(ImVec2(0,0), ImVec2(100,100), true);
ImGui::PopClipRect();

// Internal State Access
ImGui::GetStateStorage();
ImGui::GetID("string_id");
ImGui::GetID(ptr);
ImGui::GetItemRectMin();
ImGui::GetItemRectMax();
ImGui::GetItemRectSize();
*/
