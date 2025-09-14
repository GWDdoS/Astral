#include "includes.hpp"
#include "Logic/Bot/bot.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

const char* tabNames[] = {"Botting", "Hacks", "Autoclicker", "Render", "Settings", "Customization", "Mod Updates"};
const int tabCount = 7;

// Global variables (these were missing)
int currentTab = 0;
float themeColor[3] = {0.0f, 0.5f, 1.0f}; // Default blue theme
cocos2d::enumKeyCodes capturedCustomKey = cocos2d::KEY_Tab;

void applyBackgroundTheme()
{
    auto& style = ImGui::GetStyle();
    
    // Apply theme colors
    ImVec4* colors = style.Colors;
    
    // Convert RGB to ImVec4
    ImVec4 accent = ImVec4(themeColor[0], themeColor[1], themeColor[2], 1.0f);
    ImVec4 accentDark = ImVec4(themeColor[0] * 0.7f, themeColor[1] * 0.7f, themeColor[2] * 0.7f, 1.0f);
    
    // Dark theme with custom accent
    colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.95f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.95f);
    colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.3f, 0.5f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.2f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = accentDark;
    colors[ImGuiCol_FrameBgActive] = accent;
    colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = accent;
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.0f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = accentDark;
    colors[ImGuiCol_ScrollbarGrabActive] = accent;
    colors[ImGuiCol_CheckMark] = accent;
    colors[ImGuiCol_SliderGrab] = accent;
    colors[ImGuiCol_SliderGrabActive] = ImVec4(themeColor[0] * 1.2f, themeColor[1] * 1.2f, themeColor[2] * 1.2f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 0.4f);
    colors[ImGuiCol_ButtonHovered] = accentDark;
    colors[ImGuiCol_ButtonActive] = accent;
    colors[ImGuiCol_Header] = ImVec4(0.2f, 0.2f, 0.2f, 0.31f);
    colors[ImGuiCol_HeaderHovered] = accentDark;
    colors[ImGuiCol_HeaderActive] = accent;
    colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.5f);
    colors[ImGuiCol_SeparatorHovered] = accentDark;
    colors[ImGuiCol_SeparatorActive] = accent;
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered] = accentDark;
    colors[ImGuiCol_ResizeGripActive] = accent;
    colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
    colors[ImGuiCol_TabHovered] = accentDark;
    colors[ImGuiCol_TabActive] = accent;
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.0f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.0f);
    colors[ImGuiCol_PlotLinesHovered] = accent;
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.0f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.0f);
    colors[ImGuiCol_TextSelectedBg] = accentDark;
    colors[ImGuiCol_DragDropTarget] = accent;
}

void setupImGuiStyle()
{
    auto& style = ImGui::GetStyle();
    auto& io = ImGui::GetIO();
    
    // Try to load custom font, fallback to default if failed
    try {
        auto fontPath = (Mod::get()->getResourcesDir() / "font0.ttf").string();
        auto* font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.0f);
        if (!font) {
            // Fallback to default font
            io.Fonts->AddFontDefault();
        }
    } catch (...) {
        io.Fonts->AddFontDefault();
    }
    
    style.Alpha = 0.99f;
    style.WindowRounding = 12.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 8.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding = 8.0f;
    style.TabRounding = 6.0f;
    style.WindowPadding = ImVec2(15, 15);
    style.FramePadding = ImVec2(10, 6);
    style.ItemSpacing = ImVec2(12, 8);
    style.AntiAliasedLines = true;
    style.AntiAliasedFill = true;
    
    applyBackgroundTheme();
    styleApplied = true;
}

void renderBottingTab()
{
    ImGui::Text("Macro Recording System");
    ImGui::Separator();
    
    ImGui::InputFloat("TPS Value:", &tpsValue);
    if (tpsValue < 0.1f) {
        tpsValue = 0.1f;
    }
    if (tpsValue > 1000.0f) {
        tpsValue = 1000.0f;
    }
    
    ImGui::Spacing();
    
    // Recording controls
    if (!isRecording && !isPlaying) {
        if (ImGui::Button("Start Recording", ImVec2(150, 30))) {
            isRecording = true;
            Astral::Bot::StartRecording();
        }
    } else if (isRecording) {
        if (ImGui::Button("Stop Recording", ImVec2(150, 30))) {
            isRecording = false;
            Astral::Bot::StopRecording();
        }
    }
    
    ImGui::SameLine();
    
    // Playback controls
    if (!isPlaying && !isRecording) {
        if (ImGui::Button("Play Macro", ImVec2(150, 30))) {
            isPlaying = true;
            Astral::Bot::StartPlayback();
        }
    } else if (isPlaying) {
        if (ImGui::Button("Stop Playback", ImVec2(150, 30))) {
            isPlaying = false;
            Astral::Bot::StopPlayback();
        }
    }
    
    ImGui::Spacing();
    
    // Status display
    if (isRecording) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "● RECORDING");
    } else if (isPlaying) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "▶ PLAYING");
    } else {
        ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "● IDLE");
    }
    
    ImGui::Spacing();
    ImGui::Text("Macro Settings:");
    
    if (ImGui::Button("Save Macro", ImVec2(100, 25))) {
        Astral::Bot::Save();
    }
    ImGui::SameLine();
    if (ImGui::Button("Load Macro", ImVec2(100, 25))) {
        Astral::Bot::Load();
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear Macro", ImVec2(100, 25))) {
        Astral::Bot::Clear();
    }
}

void renderHacksTab()
{
    ImGui::Text("Player Modifications");
    ImGui::Separator();
    
    ImGui::Checkbox("Noclip", &noclipEnabled);
    ImGui::SameLine();
    if (ImGui::BeginMenu("Players")) {
        ImGui::Checkbox("Player 1", &noclipP1);
        ImGui::Checkbox("Player 2", &noclipP2);
        ImGui::EndMenu();
    }
    
    ImGui::Spacing();
    
    ImGui::Checkbox("Speedhack", &speedhackEnabled);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80);
    ImGui::InputFloat("##speedmult", &speedhackMultiplier, 0.1f, 1.0f, "%.2f");
    if (speedhackMultiplier < 0.01f) {
        speedhackMultiplier = 0.01f;
    }
    if (speedhackMultiplier > 10.0f) {
        speedhackMultiplier = 10.0f;
    }
    
    ImGui::Spacing();
    ImGui::Text("Visual Effects");
    ImGui::Separator();
    
    ImGui::Checkbox("Safe Mode", &safeMode);
    ImGui::Checkbox("No Death Effect", &noDeathEffect);
    ImGui::Checkbox("No Respawn Flash", &noRespawnFlash);
    ImGui::Checkbox("No Shaders", &noShaders);
    ImGui::Checkbox("No Mirror", &noMirror);
    ImGui::Checkbox("Instant Mirror", &instantMirror);
    
    ImGui::Spacing();
    ImGui::Text("Game Mechanics");
    ImGui::Separator();
    
    ImGui::SetNextItemWidth(120);
    ImGui::InputFloat("Respawn Delay", &respawnDelay, 0.1f, 1.0f, "%.1f");
    if (respawnDelay < 0.0f) {
        respawnDelay = 0.0f;
    }
    if (respawnDelay > 5.0f) {
        respawnDelay = 5.0f;
    }
    
    ImGui::Checkbox("Show Trajectory", &trajectoryEnabled);
    ImGui::Checkbox("Frame Stepper", &framestepEnabled);
}

void renderAutoClickerTab() 
{
    ImGui::Text("Auto Clicker");
    ImGui::Separator();
    ImGui::Text("Auto clicker functionality will be implemented here.");
}

void renderRenderTab()
{
    ImGui::Text("Recording & Display");
    ImGui::Separator();
    
    ImGui::Checkbox("Show Layout", &layoutEnabled);
    
    ImGui::Spacing();
    
    if (ImGui::Button("Start Render", ImVec2(150, 30))) {
        // TODO: Implement render start
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop Render", ImVec2(150, 30))) {
        // TODO: Implement render stop
    }
    
    ImGui::Spacing();
    ImGui::Text("Debug Display");
    ImGui::Separator();
    
    ImGui::Checkbox("Show Hitboxes", &showHitboxes);
    ImGui::Checkbox("Show Grid", &showGrid);
}

void renderSettingsTab()
{
    ImGui::Text("Keybinds");
    ImGui::Separator();
    
    ImGui::Text("Toggle GUI Key:");
    
    const char* currentKeyDisplay = getKeyName(capturedCustomKey);
    if (ImGui::Button(isCapturingKeybind ? "Press any key..." : currentKeyDisplay, ImVec2(120, 25))) {
        isCapturingKeybind = true; 
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
    ImGui::Text("Theme Settings");
    ImGui::Separator();
    
    ImGui::Text("Accent Color:");
    if (ImGui::ColorEdit3("##accentcolor", themeColor)) {
        applyBackgroundTheme(); // Apply theme when color changes
    }
    
    ImGui::Spacing();
    
    if (ImGui::Button("Reset to Default")) {
        themeColor[0] = 0.0f;
        themeColor[1] = 0.5f;
        themeColor[2] = 1.0f;
        applyBackgroundTheme();
    }
}

void renderTodoTab()
{
    ImGui::Text("Development Status");
    ImGui::Separator();
    
    ImGui::BulletText("Current state of the mod's development");
    ImGui::Spacing();
    
    ImGui::Text("Completed:");
    ImGui::BulletText("Basic GUI framework");
    ImGui::BulletText("Macro recording structure");
    ImGui::BulletText("Theme customization");
    
    ImGui::Spacing();
    ImGui::Text("In Progress:");
    ImGui::BulletText("Macro playback system");
    ImGui::BulletText("Hack implementations");
    ImGui::BulletText("Auto clicker functionality");
    
    ImGui::Spacing();
    ImGui::Text("Planned:");
    ImGui::BulletText("Render system");
    ImGui::BulletText("Settings persistence");
    ImGui::BulletText("Advanced macro features");
}

void renderMainGui()
{
    if (!ImGui::GetCurrentContext()) return;
    
    auto& imguiCocos = ImGuiCocos::get();
    if (&imguiCocos == nullptr) return;
    
    guiVisible = imguiCocos.isVisible();
    if (!guiVisible) return;
    
    if (!styleApplied) {
        setupImGuiStyle();
    }
    
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
    
    // Set window size
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    
    if (!ImGui::Begin("Astral [BETA]", nullptr, flags)) {
        ImGui::End();
        return;
    }
    
    // Title
    float width = ImGui::GetContentRegionAvail().x;
    const char* title = "Astral [BETA]";
    ImGui::SetCursorPosX((width - ImGui::CalcTextSize(title).x) * 0.5f);
    ImGui::Text("%s", title);
    ImGui::Separator();
    
    // Tab buttons
    for (int i = 0; i < tabCount; i++) {
        if (tabNames[i]) {
            bool selected = (currentTab == i);
            if (selected) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
            }
            
            if (ImGui::Button(tabNames[i])) {
                currentTab = i;
            }
            
            if (selected) {
                ImGui::PopStyleColor();
            }
            
            if (i < tabCount - 1) {
                ImGui::SameLine();
            }
        }
    }
    
    ImGui::Separator();
    ImGui::Spacing();
    
    // Render current tab
    switch (currentTab) {
        case 0: renderBottingTab(); break;
        case 1: renderHacksTab(); break;
        case 2: renderAutoClickerTab(); break;
        case 3: renderRenderTab(); break;
        case 4: renderSettingsTab(); break;
        case 5: renderCustomizationTab(); break;
        case 6: renderTodoTab(); break;
        default: ImGui::Text("Invalid tab selected."); break;
    }
    
    ImGui::End();
}