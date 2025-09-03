#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "includes.h"
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/Geode.hpp>
#include <imgui-cocos.hpp>

using namespace geode::prelude;

/* de3am is a boykisser and a list helper
   Breuhh is also a boykisser and a list helper. (de3am told me to put this) 
*/
// OMG its all gone :sob: 
// omg its all back :D

bool noclipEnabled = false;
bool recording = false;
bool replaying = false;
bool rendering = false;
int selectedTheme = 0;
bool layoutEnabled = false;
bool oldphysEnabled = false;
float seedValue = 1.0f;
float fpsValue = 240.0f;

// Theme and style variables
float themeColor[3] = {0.4f, 1.0f, 0.7f};  // Mint green RGB
bool styleApplied = false;

// Keybind variables
int selectedKeybind = 0;  // 0 = Alt, 1 = F1, 2 = F2, 3 = F3, etc.
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
        // Setup callback - runs after imgui initialization
        auto& style = ImGui::GetStyle();
        auto& io = ImGui::GetIO();
        
        // Make the font less pixelated and bigger
        io.FontGlobalScale = 1.2f;
        
        // Apply mint green theme with curved edges
        style.WindowRounding = 12.0f;
        style.FrameRounding = 8.0f;
        style.PopupRounding = 8.0f;
        style.ScrollbarRounding = 8.0f;
        style.GrabRounding = 8.0f;
        style.TabRounding = 8.0f;
        style.ChildRounding = 8.0f;
        
        // Make it 200% bigger
        style.ScaleAllSizes(2.0f);
        
        // Mint green color scheme
        ImVec4 mintGreen = ImVec4(0.4f, 1.0f, 0.7f, 1.0f);
        ImVec4 darkMintGreen = ImVec4(0.3f, 0.8f, 0.55f, 1.0f);
        ImVec4 lightMintGreen = ImVec4(0.5f, 1.0f, 0.8f, 1.0f);
        ImVec4 mintAccent = ImVec4(0.2f, 0.9f, 0.6f, 1.0f);
        
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.9f);
        style.Colors[ImGuiCol_TitleBg] = darkMintGreen;
        style.Colors[ImGuiCol_TitleBgActive] = mintGreen;
        style.Colors[ImGuiCol_Button] = darkMintGreen;
        style.Colors[ImGuiCol_ButtonHovered] = mintGreen;
        style.Colors[ImGuiCol_ButtonActive] = mintAccent;
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.2f, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.3f, 0.3f, 0.3f, 0.8f);
        style.Colors[ImGuiCol_FrameBgActive] = mintAccent;
        style.Colors[ImGuiCol_CheckMark] = mintGreen;
        style.Colors[ImGuiCol_SliderGrab] = mintGreen;
        style.Colors[ImGuiCol_SliderGrabActive] = lightMintGreen;
        style.Colors[ImGuiCol_Header] = darkMintGreen;
        style.Colors[ImGuiCol_HeaderHovered] = mintGreen;
        style.Colors[ImGuiCol_HeaderActive] = lightMintGreen;
        style.Colors[ImGuiCol_Tab] = darkMintGreen;
        style.Colors[ImGuiCol_TabHovered] = mintGreen;
        style.Colors[ImGuiCol_TabActive] = lightMintGreen;
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.2f, 0.6f, 0.4f, 0.8f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = darkMintGreen;
        
        styleApplied = true;
   }).draw([] {
        // Apply custom theme colors if changed
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
        
        // Always wrap ImGui content in a window
        if (ImGui::Begin("Astral Mod", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Separator();
            
            if (ImGui::BeginTabBar("##tabs")) {
                if (ImGui::BeginTabItem("Hacks")) {
                    ImGui::Separator();
                    ImGui::Checkbox("Enable Noclip", &noclipEnabled);
                    ImGui::Checkbox("Show Layout", &layoutEnabled);
                    ImGui::InputFloat("Lock Seed", &seedValue);
                    
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Botting")) {
                    ImGui::Separator();
                    if (ImGui::Button("Record Macro")) {
                        // Add macro recording functionality here
                    }
                    if (ImGui::Button("Save Macro")) {
                        // Add macro saving functionality here  
                    }
                    ImGui::InputFloat("FPS", &fpsValue);
                    ImGui::Checkbox("Enable 2.1 Legacy Physics", &oldphysEnabled);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("AutoClicker")) {
                    ImGui::Separator();
                    if (ImGui::Button("Start AutoClicker")) {
                        // Add autoclicker functionality here
                    }
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Render")) {
                    ImGui::Separator();
                    if (ImGui::Button("Start Render")) {
                        // Add render functionality here
                    }
                    if (ImGui::Button("Stop Render")) {
                        // Add render functionality here
                    }
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Settings")) {
                    ImGui::Separator();
                    ImGui::Text("GUI Settings:");
                    ImGui::Separator();
                    
                    // Keybind selector
                    ImGui::Text("Toggle GUI Key:");
                    if (ImGui::Combo("##keybind", &selectedKeybind, keybindNames, IM_ARRAYSIZE(keybindNames))) {
                        // Keybind changed - could save to config here
                    }
                    
                    ImGui::Text("Current Key: %s", keybindNames[selectedKeybind]);
                    
                    // Color chooser
                    ImGui::Separator();
                    ImGui::Text("Theme Color:");
                    if (ImGui::ColorEdit3("##themecolor", themeColor)) {
                        // Color changed - theme updates automatically
                    }
                    
                    // Reset to mint green button
                    if (ImGui::Button("Reset to Mint Green")) {
                        themeColor[0] = 0.4f; // R
                        themeColor[1] = 1.0f; // G  
                        themeColor[2] = 0.7f; // B
                    }
                    
                    // Other settings can go here
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
        // Check if the pressed key matches the selected keybind
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
