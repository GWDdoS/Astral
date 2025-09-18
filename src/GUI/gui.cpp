#include "includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

const char* tabNames[] = {"Botting", "Hacks", "Assists", "Render", "Settings", "Mod Updates"};
const int tabCount = 6;

int currentTab = 0;
float themeColor[3] = {0.0f, 0.0f, 0.0f};
// bool styleApplied = false;
// bool guiVisible = false;

float getCurrentFrame() {
    auto* playLayer = PlayLayer::get();
    if (!playLayer) return 0.0f;
    
    // The game already tracks time in seconds
    float currentTime = playLayer->m_gameState.m_levelTime;
    
    // Convert time to frames using current TPS
    float currentFrame = currentTime * tpsValue; // Default 240 TPS
    
    return currentFrame;
}

#ifdef GEODE_IS_DESKTOP // i think this is how u do it
// yes this is how u do it - slideglide

void applyBackgroundTheme()
{
    auto& style = ImGui::GetStyle();
}

void setupImGuiStyle()
{
    auto& style = ImGui::GetStyle();
    auto& io = ImGui::GetIO();
    auto* font = io.Fonts->AddFontFromFileTTF(
        (Mod::get()->getResourcesDir() / ("font" + std::to_string(0) + ".ttf")).string().c_str(), 16.0f
    );
    
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
    if (ImGui::Button("Record Macro", ImVec2(150, 30))) {}
    ImGui::SameLine();
    if (ImGui::Button("Play Macro", ImVec2(150, 30))) {}
    ImGui::Spacing();
    ImGui::InputFloat("TPS Value:", &tpsValue);
    if (tpsValue < 0.f) {
        tpsValue = 240.f;
    }
    ImGui::Checkbox("Show Trajectory", &trajectoryEnabled);
    ImGui::Checkbox("Frame Stepper", &framestepEnabled);
}

void renderHacksTab()
{       // lets see if i can learn columns
    ImGui::Columns(2, "HacksColumns", false); 
    ImGui::SetColumnWidth(0, 200.0f);
    ImGui::SetColumnWidth(1, 200.0f);
    
    ImGui::Checkbox("Noclip", &noclipEnabled);
    ImGui::SameLine();
    
    if (ImGui::Button("Players")) {
        ImGui::OpenPopup("PlayersPopup");
    }
    
    if (ImGui::BeginPopup("PlayersPopup")) {
        ImGui::Checkbox("Player 1", &noclipP1);
        ImGui::Checkbox("Player 2", &noclipP2);
        ImGui::EndPopup();
    }
    
    ImGui::Checkbox("Speedhack", &speedhackEnabled);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80.0f);
    ImGui::InputFloat("##SpeedMultiplier", &speedhackMultiplier);
    if (speedhackMultiplier < 0.f) {
        speedhackMultiplier = 1.f;
    }
    
    ImGui::Text("Respawn Time");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80.0f);
    ImGui::InputFloat("##RespawnDelay", &respawnDelay);
    if (respawnDelay != 0.f && respawnDelay != 2.f) {
        respawnDelay = (fabs(respawnDelay - 0.f) < fabs(respawnDelay - 2.f)) ? 0.f : 2.f;
    }
    ImGui::Spacing();
    ImGui::Checkbox("Safe Mode", &safeMode);
    ImGui::NextColumn();
    
    ImGui::Checkbox("No Death Effect", &noDeathEffect);
    ImGui::Checkbox("No Respawn Flash", &noRespawnFlash);
    
    ImGui::Spacing();
    
    ImGui::Checkbox("No Shaders", &noShaders);
    ImGui::Checkbox("No Mirror", &noMirror);
    ImGui::Checkbox("Instant Mirror", &instantMirror);   
    ImGui::Checkbox("Keep Waveform", &keepWaveEnabled);     
    ImGui::Columns(1);
}

void renderAssists() 
{
    ImGui::Checkbox("Autoclicker Enable", &autoClickerEnabled);
    
    if (autoClickerEnabled) {
        ImGui::Separator();
        
        auto renderButtonSettings = [](const char* buttonName, AutoClickerSettings& settings) {
            if (ImGui::CollapsingHeader(buttonName)) {
                ImGui::Indent();
                
                ImGui::Checkbox("Enable", &settings.enabled);
                
                if (settings.enabled) {
                    ImGui::Text("Timing:");
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Hold Frames", &settings.intervalHold);
                    if (settings.intervalHold < 1) settings.intervalHold = 1;
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames", &settings.intervalRelease);
                    if (settings.intervalRelease < 1) settings.intervalRelease = 1;
                    
                    ImGui::Text("Advanced:");
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame", &settings.clicksPerFrame);
                    if (settings.clicksPerFrame < 1) settings.clicksPerFrame = 1;
                    if (settings.clicksPerFrame > 10) settings.clicksPerFrame = 10;
                    
                    ImGui::Checkbox("Swift Click", &settings.swiftClick);
                    ImGui::SameLine();
                    if (ImGui::Button("?")) {
                        ImGui::SetTooltip("Instantly releases the same frame as the click");
                    }
                    
                    ImGui::Checkbox("Limit Frames", &settings.limitFrames);
                    if (settings.limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames", &settings.maxFrames);
                        if (settings.maxFrames < 0) settings.maxFrames = 0;
                    }
                }
                
                ImGui::Unindent();
            }
        };
        
        renderButtonSettings("W Key", autoClick_W);
        renderButtonSettings("A Key", autoClick_A);
        renderButtonSettings("S Key", autoClick_S);
        renderButtonSettings("UP Key", autoClick_UP);
        renderButtonSettings("LEFT Key", autoClick_LEFT);
        renderButtonSettings("RIGHT Key", autoClick_RIGHT);
        renderButtonSettings("SPACE Key", autoClick_SPACE);
        
        ImGui::Separator();
        
        if (ImGui::CollapsingHeader("Presets")) {
            ImGui::Text("Apply preset to:");
            static int presetTarget = 0;
            const char* buttons[] = {"W", "A", "S", "UP", "LEFT", "RIGHT", "SPACE"};
            ImGui::Combo("Target Button", &presetTarget, buttons, 7);
            
            ImGui::Spacing();
            
            if (ImGui::Button("Rapid Fire (1-1)")) {
                AutoClickerSettings* target = nullptr;
                switch(presetTarget) {
                    case 0: target = &autoClick_W; break;
                    case 1: target = &autoClick_A; break;
                    case 2: target = &autoClick_S; break;
                    case 3: target = &autoClick_UP; break;
                    case 4: target = &autoClick_LEFT; break;
                    case 5: target = &autoClick_RIGHT; break;
                    case 6: target = &autoClick_SPACE; break;
                }
                if (target) {
                    target->enabled = true;
                    target->intervalHold = 1;
                    target->intervalRelease = 1;
                    target->clicksPerFrame = 1;
                    target->swiftClick = true;
                }
            }
            
            ImGui::SameLine();
            if (ImGui::Button("Slow Click (10-5)")) {
                AutoClickerSettings* target = nullptr;
                switch(presetTarget) {
                    case 0: target = &autoClick_W; break;
                    case 1: target = &autoClick_A; break;
                    case 2: target = &autoClick_S; break;
                    case 3: target = &autoClick_UP; break;
                    case 4: target = &autoClick_LEFT; break;
                    case 5: target = &autoClick_RIGHT; break;
                    case 6: target = &autoClick_SPACE; break;
                }
                if (target) {
                    target->enabled = true;
                    target->intervalHold = 10;
                    target->intervalRelease = 5;
                    target->clicksPerFrame = 1;
                    target->swiftClick = false;
                }
            }
            
            ImGui::SameLine();
            if (ImGui::Button("Disable All")) {
                autoClick_W.enabled = false;
                autoClick_A.enabled = false;
                autoClick_S.enabled = false;
                autoClick_UP.enabled = false;
                autoClick_LEFT.enabled = false;
                autoClick_RIGHT.enabled = false;
                autoClick_SPACE.enabled = false;
            }
        }
    }
    
    ImGui::Separator();
    ImGui::BulletText("More assists coming soon!");
}

void renderRenderTab()
{
    ImGui::Checkbox("Show Layout", &layoutEnabled);
    if (ImGui::Button("Start Render", ImVec2(150, 30))) {}
    ImGui::SameLine();
    if (ImGui::Button("Stop Render", ImVec2(150, 30))) {}
    ImGui::Spacing();
    ImGui::Checkbox("Show Hitboxes", &showHitboxes);
    ImGui::Checkbox("Show Grid", &showGrid);
}

void renderSettingsTab()
{
    ImGui::Text("Toggle GUI Key:");
    
    const char* currentKeyDisplay = getKeyName(capturedCustomKey);
    if (ImGui::Button(isCapturingKeybind ? "Press any key..." : currentKeyDisplay, ImVec2(120, 25))) {
        isCapturingKeybind = true; 
    }
    // my dumbass had isCapturingKeybind = true; twice :rip:
    if (isCapturingKeybind)
    {
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            isCapturingKeybind = false;
        }
    }
    
    ImGui::Text("Current Key: %s", currentKeyDisplay);
    ImGui::Text("Accent Color:");
    ImGui::ColorEdit3("##accentcolor", themeColor);
}

void renderTodoTab()
{
    ImGui::BulletText("A current state of the mods development");
}

void renderMainGui()
{
    if (!ImGui::GetCurrentContext()) return;
    
    auto& imguiCocos = ImGuiCocos::get();
    if (&imguiCocos == nullptr) return;
    
    guiVisible = imguiCocos.isVisible();
    if (tabCount <= 0) return;
    
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
    if (!ImGui::Begin("Astral [BETA]", nullptr, flags)) {
        ImGui::End();
        return;
    }
    
    float width = ImGui::GetContentRegionAvail().x;
    const char* title = "Astral [BETA]";
    ImGui::SetCursorPosX((width - ImGui::CalcTextSize(title).x) * 0.5f);
    ImGui::Text("%s", title);
    ImGui::Separator();
    
    for (int i = 0; i < tabCount; i++) {
    }
    if (!tabNames || tabCount <= 0) return;
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
    
    bool open = ImGui::Begin("Astral [BETA]", nullptr, window_flags);
    if (!open) return;
    ImGui::End();
    ImGui::SetCursorPosY(70);
    
    for (int i = 0; i < tabCount; i++)
    {
        if (!tabNames[i]) continue;
        if (ImGui::Button(tabNames[i])) currentTab = i;
        if (i < tabCount - 1) ImGui::SameLine();
    }
    
    ImGui::Separator();
    
    switch (currentTab) {
        case 0: renderBottingTab(); break;
        case 1: renderHacksTab(); break;
        case 2: renderAssists(); break;
        case 3: renderRenderTab(); break;
        case 4: renderSettingsTab(); break;
        case 5: renderTodoTab(); break;
    }
    
    ImGui::Separator();
    float currentFrame = getCurrentFrame();
    ImGui::Text("Frame: %.2f", currentFrame);
    
    ImGui::End();
}
#endif

#ifdef GEODE_IS_MOBILE
// this should do the Mobile Cocos GUI
class $modify(MenuLayer) {
    void onMoreGames(CCObject* target) {
        Astral_GUI_Mobile_UI::create()->show();
    }
};
#endif