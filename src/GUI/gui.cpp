#include "includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

const char* tabNames[] = {"Botting", "Hacks", "Assists", "Autoclicker", "Render", "Settings"};
const int tabCount = 6;

int currentTab = 0;
float themeColor[3] = {0.0f, 0.0f, 0.0f};
float frameCount = 0.0f;
bool initialized = false;
static float lastLevelTime = 0.0f;
static float lastProgress = 0.0f;

float getCurrentFrame() {
    auto* playLayer = PlayLayer::get();
    if (!playLayer) {
        frameCount = 0.0f;
        initialized = false;
        lastLevelTime = 0.0f;
        lastProgress = 0.0f;
        return 0.0f;
    }
    
    float currentTime = playLayer->m_gameState.m_levelTime;
    float currentProgress = playLayer->m_gameState.m_currentProgress;
    
    if (initialized && (currentProgress < lastProgress - 0.01f || currentTime < lastLevelTime - 0.01f)) {
        frameCount = 0.0f;
        initialized = false;
        lastLevelTime = 0.0f;
    }
    
    if (!playLayer->m_hasCompletedLevel && 
        !playLayer->m_isPaused && 
        currentProgress > 0.0f) {
            
            if (!initialized) {
                frameCount = 0.0f;
                lastLevelTime = currentTime;
                initialized = true;
            } else {
                float deltaTime = currentTime - lastLevelTime;
                float deltaFrames = deltaTime * tpsValue;
                
                frameCount += deltaFrames;
                lastLevelTime = currentTime;
            }
        } else if (!initialized) {
            frameCount = 0.0f;
            lastLevelTime = currentTime;
            initialized = true;
        }
        
        lastProgress = currentProgress;
        
        return frameCount;
    }
    
    #ifdef GEODE_IS_DESKTOP
    
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
        
        styleApplied = true;
    }
    
    void renderBottingTab()
    {
        static std::string macroName = "";
        static char macroBuffer[256] = "";
        
        ImGui::Text("Macro Name:");
        if (ImGui::InputText("##MacroName", macroBuffer, sizeof(macroBuffer))) {
            macroName = std::string(macroBuffer);
        }
        
        ImGui::Spacing();
        
        if (ImGui::Button("Record Macro", ImVec2(150, 30))) {
        }
        ImGui::SameLine();
        if (ImGui::Button("Play Macro", ImVec2(150, 30))) {
        }
        
        ImGui::Spacing();
        ImGui::InputFloat("TPS Value:", &tpsValue);
        if (tpsValue < 0.f) {
            tpsValue = 240.f;
        }
        ImGui::Checkbox("Show Trajectory", &trajectoryEnabled);
        ImGui::Spacing();
        ImGui::Checkbox("Frame Stepper", &framestepEnabled);
        ImGui::Spacing();
        ImGui::Checkbox("Show Layout", &layoutEnabled);
        ImGui::Spacing();
        ImGui::Checkbox("Show Hitboxes", &showHitboxes);
    }
    
    void renderHacksTab()
    {
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
        if (respawnDelay < 0.f) {
            respawnDelay = 1.f;
        } else if (respawnDelay > 2.f){
            respawnDelay = 1.f;
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
        ImGui::Checkbox("Keep Wave On", &keepWaveEnabled);     
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::Checkbox("Unlock Everything", &unlockEverything);
        ImGui::Checkbox("Accurate Percentage", &accuratePercentage);
        ImGui::SameLine();
        ImGui::InputInt("##DecimalPlaces", &decimalPlaces);
        if (decimalPlaces < 0) {
            decimalPlaces = 1;
        } else if (decimalPlaces > 20){
            decimalPlaces = 1;
        }
        ImGui::Separator();
        ImGui::Checkbox("Seed Hack", &seedHackEnabled);
        ImGui::SameLine();
        ImGui::InputInt("##Seed", &seedValue);
    }
    
    void renderAssists()
    {
        
    }
    
    struct AutoKeyGUI {
        const char* label;    // Display name in the header
        const char* id;       // Unique ImGui suffix (##ID)
        bool* enabled;
        int* hold;
        int* release;
        int* clicks;
        bool* swift;
        bool* limitFrames;
        int* maxFrames;
    };
    // lets see what it came up with. I dont want to use smt ik wont work
    struct AutoKeyGUI {
        const char* label;
        const char* id;
        bool* enabled;
        int* hold;
        int* release;
        int* clicks;
        bool* swift;
        bool* limitFrames;
        int* maxFrames;
        bool* blackOrbMode;
        int* blackOrbClicks;
        int* blackOrbHold;
    };
    /*
    static void RenderKeySettings(const AutoKeyGUI& k) {
        if (ImGui::CollapsingHeader(k.label)) {
            ImGui::Indent();
            ImGui::Checkbox(fmt::format("Enable{}", k.id).c_str(), k.enabled);
            
            if (*k.enabled) {
                // Hold Frames with special case for infinite hold (0)
                ImGui::SetNextItemWidth(100);
                ImGui::InputInt(fmt::format("Hold Frames{}", k.id).c_str(), k.hold);
                if (*k.hold < 0) *k.hold = 0;
                
                // Show helpful text for hold mode
                if (*k.hold == 0) {
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.5f, 1.0f), "(Infinite Hold)");
                }
                
                // Only show release frames if not in infinite hold mode
                if (*k.hold > 0) {
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt(fmt::format("Release Frames{}", k.id).c_str(), k.release);
                    *k.release = std::max(1, *k.release);
                }
                
                ImGui::SetNextItemWidth(80);
                ImGui::InputInt(fmt::format("Clicks/Frame{}", k.id).c_str(), k.clicks);
                *k.clicks = std::clamp(*k.clicks, 1, 10);
                
                ImGui::Checkbox(fmt::format("Swift Click{}", k.id).c_str(), k.swift);
                ImGui::Checkbox(fmt::format("Limit Frames{}", k.id).c_str(), k.limitFrames);
                
                if (*k.limitFrames) {
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt(fmt::format("Max Frames{}", k.id).c_str(), k.maxFrames);
                    *k.maxFrames = std::max(0, *k.maxFrames);
                }
                
                // Black orb mode settings
                ImGui::Separator();
                ImGui::Checkbox(fmt::format("Black Orb Mode{}", k.id).c_str(), k.blackOrbMode);
                
                if (*k.blackOrbMode) {
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt(fmt::format("Orb Clicks{}", k.id).c_str(), k.blackOrbClicks);
                    *k.blackOrbClicks = std::max(1, *k.blackOrbClicks);
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt(fmt::format("Orb Hold Frames{}", k.id).c_str(), k.blackOrbHold);
                    *k.blackOrbHold = std::max(1, *k.blackOrbHold);
                }
            }
            ImGui::Unindent();
        }
    }
    
    void renderAutoclicker() {
        ImGui::Checkbox("Autoclicker Enable", &autoClickerEnabled);
        if (!autoClickerEnabled) return;
        
        ImGui::Separator();
        
        // Add helpful text about hold mode
        ImGui::TextColored(ImVec4(0.7f, 0.7f, 1.0f, 1.0f), "Tip: Set Hold Frames to 0 for infinite hold mode");
        ImGui::Spacing();
        
        ImGui::Text("Player 1 Controls:");
        
        AutoKeyGUI player1Keys[] = {
            {"W Key (Player 1 Jump)", "##W", &autoClick_W_enabled, &autoClick_W_intervalHold,
                &autoClick_W_intervalRelease, &autoClick_W_clicksPerFrame,
                &autoClick_W_swiftClick, &autoClick_W_limitFrames, &autoClick_W_maxFrames,
                &autoClick_W_blackOrbModeEnabled, &autoClick_W_blackOrb_clickCount, &autoClick_W_blackOrb_holdFrames,}
        }
    }        
    */            
                void renderRenderTab()
                {
                    if (ImGui::Button("Start Render", ImVec2(150, 30))) {}
                    ImGui::SameLine();
                    if (ImGui::Button("Stop Render", ImVec2(150, 30))) {}
                    ImGui::Spacing();
                }
                
                void renderSettingsTab()
                {
                    ImGui::Text("Toggle GUI Key:");
                    
                    const char* currentKeyDisplay = getKeyName(capturedCustomKey);
                    if (ImGui::Button(isCapturingKeybind ? "Press any key..." : currentKeyDisplay, ImVec2(120, 25))) {
                        isCapturingKeybind = true; 
                    }
                    
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
                
                void renderMainGui()
                {
                    if (!ImGui::GetCurrentContext()) return;
                    
                    auto& imguiCocos = ImGuiCocos::get();
                    if (&imguiCocos == nullptr) return;
                    
                    guiVisible = imguiCocos.isVisible();
                    if (tabCount <= 0) return;
                    
                    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
                    if (!ImGui::Begin("Astral [BETA v1]", nullptr, flags)) {
                        ImGui::End();
                        return;
                    }
                    
                    float width = ImGui::GetContentRegionAvail().x;
                    const char* title = "Astral [BETA v1]";
                    ImGui::SetCursorPosX((width - ImGui::CalcTextSize(title).x) * 0.5f);
                    ImGui::Text("%s", title);
                    ImGui::Separator();
                    
                    if (!tabNames || tabCount <= 0) {
                        ImGui::End();
                        return;
                    }
                    
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
                        case 3: renderAutoclicker(); break;
                        case 4: renderRenderTab(); break;
                        case 5: renderSettingsTab(); break; 
                    }
                    
                    ImGui::Separator();
                    float currentFrame = getCurrentFrame();
                    ImGui::Text("Frame: %.2f", currentFrame);
                    
                    ImGui::End();
                }
                
                #endif
                
                #ifdef GEODE_IS_MOBILE
                class $modify(MenuLayer) {
                    void onMoreGames(CCObject* target) {
                        Astral_GUI_Mobile_UI::create()->show();
                    }
                };
                #endif