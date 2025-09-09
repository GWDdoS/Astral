#include "../includes.hpp"

using namespace geode::prelude;
// I like the vars being orginized
const char* getKeyName(cocos2d::enumKeyCodes keyCode);
const char* tabNames[] = {"Botting", "Hacks", "AutoClicker", "Render", "Settings", "Customization"};
bool currentGuiState = ImGuiCocos::get().isVisible();
bool showHitboxes = false;
bool showGrid = false;
const int tabCount = 7; // you have to change this when u add a tag lmfao
int currentTab = 0;
float themeColor[3] = {0.0f,0.0f,0.0f};


void applyBackgroundTheme()
{
    auto &style = ImGui::GetStyle();
}

void setupImGuiStyle()
{
    // this is all the style stuff, font, colors, etc.
    auto& style = ImGui::GetStyle();
    auto& io = ImGui::GetIO();
    auto* font = ImGui::GetIO().Fonts->AddFontFromFileTTF((Mod::get()->getResourcesDir() / ("font" + std::to_string(fontType) + ".ttf")).string().c_str(), 16.0f);
    /*
    style.Alpha = 0.99f; // bg opacity  
    style.WindowRounding = 12.0f; // rounding between menus (it also says rounding dumbass)
    style.ChildRounding = 8.0f; 
    style.FrameRounding = 8.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 8.0f;
    style.TabRounding = 6.0f;
    style.WindowPadding = ImVec2(15, 15); // Spaces between shit
    style.FramePadding = ImVec2(10, 6);
    style.ItemSpacing = ImVec2(12, 8);
    style.AntiAliasedLines = true; // idk fully what these do, i looked up what they do and they fix lines or smt so idk maybe it will look cool
    style.AntiAliasedFill = true;
    
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
    
    
    ImGui::Checkbox("Show Hitboxes", &showHitboxes);
    
    ImGui::Checkbox("Show Grid", &showGrid);
}

void renderSettingsTab()
{
    ImGui::Text("GUI Settings:");
    ImGui::Separator();
    
    ImGui::Text("Toggle GUI Key:");
    
    
    const char* currentKeyDisplay = getKeyName(capturedCustomKey); // DONT MOVE THIS LMFAO IT WILL BREAK EVERYTHING
    
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
void renderTodoTab()
{
    ImGui::Separator();
    ImGui::BulletText("A list of todo"); 
    
    
}
void renderMainGui()
{
    if (styleApplied) { 
    }
    // windows flags, changes main context about the gui  | ImGuiWindowFlags_AlwaysAutoResize
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
    
    if (currentGuiState != guiVisible) {
        guiVisible = currentGuiState;
    }
    
    // nullprt, X calls certin flags/shit for making the gui. If you dont have these the WindowFlags wont be called. 
    if (ImGui::Begin("Astral [BETA]", nullptr, window_flags)) {
        
    }
    
    ImGui::SetCursorPosY(70); // moves the thing
    // if button pressed set the tabCont=?
    for (int i = 0; i < tabCount; i++) { 
        if (ImGui::Button(tabNames[i], ImVec2(120, 30))) {
            currentTab = i;
        }
        if (i < tabCount - 1) ImGui::SameLine();
    }
    
    
    float totalTabWidth = (120 * tabCount) + (ImGui::GetStyle().ItemSpacing.x * (tabCount - 1));
    
    
    ImGui::Separator();
    ImGui::Spacing();
    // to switch the gui cahnge render 
    switch (currentTab) {
        case 0: renderBottingTab(); break;
        case 1: renderHacksTab(); break;
        case 2: renderAutoClickerTab(); break;
        case 3: renderRenderTab(); break;
        case 4: renderSettingsTab(); break;
        case 5: renderCustomizationTab(); break;
        case 6: renderTodoTab(); break;
    }
    ImGui::End();
}
