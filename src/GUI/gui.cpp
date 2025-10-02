#include "includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);
const char* tabNames[] = {"Botting", "Hacks", "Assists", "Autoclicker", "Render", "Settings"};
const int tabCount = 6;

int currentTab = 0;
float themeColor[3] = {0.0f, 0.0f, 0.0f};
float frameCount = 0.0f;
bool initialized = false;
float lastLevelTime = 0.0f;
float lastProgress = 0.0f;
float tpsValue = 240.0f;
// added debug logs to figure this shit out (ty claude for the idea and shit)
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
    
    // check if level is actually playing
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
    
    
    class $modify(AstralFrameCounter, PlayLayer) {
        void update(float dt) {
            PlayLayer::update(dt);
            getCurrentFrame();
        }
        
        void resetLevel() {
            frameCount = 0.0f;
            initialized = false;
            lastLevelTime = 0.0f;
            lastProgress = 0.0f;
            PlayLayer::resetLevel();
        }
        
        void onQuit() {
            frameCount = 0.0f;
            initialized = false;
            lastLevelTime = 0.0f;
            lastProgress = 0.0f;
            PlayLayer::onQuit();
        }
    };
    
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
        
        if (needsRefresh) {
            refreshMacroList();
        }
        
        ImGui::Text("Select Macro:");
        
        if (availableMacros.empty()) {
            refreshMacroList();
        }
        
<<<<<<< Updated upstream
        ImGui::SetNextItemWidth(200);
        if (ImGui::BeginCombo("##MacroSelect", availableMacros[selectedMacroIndex].c_str())) {
            for (int i = 0; i < availableMacros.size(); i++) {
                bool isSelected = (selectedMacroIndex == i);
                if (ImGui::Selectable(availableMacros[i].c_str(), isSelected)) {
                    selectedMacroIndex = i;
                    
                    if (availableMacros[i] == "+ Create New") {
                        macroBuffer[0] = '\0';
                        macroName = "";
                    } else {
                        #ifndef GEODE_IS_MACOS 
                        strncpy_s(macroBuffer, availableMacros[i].c_str(), sizeof(macroBuffer) - 1);
                        #else
                        strncpy(macroBuffer, availableMacros[i].c_str(), sizeof(macroBuffer) - 1);
                        #endif
                        macroBuffer[sizeof(macroBuffer) - 1] = '\0';
                        macroName = availableMacros[i];
                    }
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        
=======

>>>>>>> Stashed changes
        ImGui::Spacing();
        
        ImGui::Text("Macro Name:");
        if (ImGui::InputText("##MacroName", macroBuffer, sizeof(macroBuffer))) {
            macroName = std::string(macroBuffer);
        }
        
        ImGui::Spacing();
        
        if (ImGui::Button("Record", ImVec2(110, 30))) {
            
        }
        ImGui::SameLine();
        if (ImGui::Button("Play", ImVec2(110, 30))) {
        }
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        ImGui::InputFloat("TPS Value:", &tpsValue);
        if (tpsValue < 0.f) {
            tpsValue = 240.f;
        }
        if (ImGui::Checkbox("Show Trajectory", &trajectoryEnabled)) {
            Mod::get()->setSavedValue("trajectory-enabled", trajectoryEnabled);
        }
        ImGui::Spacing();
        if (ImGui::Checkbox("Noclip", &noclipEnabled)) {
            Mod::get()->setSavedValue("noclip-enabled", noclipEnabled);
        }
        ImGui::SameLine();
        if (ImGui::Button("Players")) {
            ImGui::OpenPopup("NoclipPlayersPopup");
        }
        if (ImGui::BeginPopup("NoclipPlayersPopup")) {
            if (ImGui::Checkbox("Player 1", &noclipP1)) {
                Mod::get()->setSavedValue("noclip-p1", noclipP1);
            }
            if (ImGui::Checkbox("Player 2", &noclipP2)) {
                Mod::get()->setSavedValue("noclip-p2", noclipP2);
            }
            ImGui::EndPopup();
        }
        ImGui::Spacing();
        if (ImGui::Checkbox("Speedhack", &speedhackEnabled)) {
            Mod::get()->setSavedValue("speedhack-enabled", speedhackEnabled);
        }
        ImGui::SameLine();
        if (ImGui::InputFloat("Multiplier", &speedhackMultiplier)) {
            if (speedhackMultiplier <= 0.f) {
                speedhackMultiplier = 1.0f;
            }
            Mod::get()->setSavedValue("speed-hack-multiplier", speedhackMultiplier);
        }
        ImGui::Spacing();
<<<<<<< Updated upstream
        if (ImGui::Checkbox("Seedhack", &seedHackEnabled)) {
            Mod::get()->setSavedValue("seed-hack-enabled", seedHackEnabled);
        }
        ImGui::SameLine();
        if (ImGui::InputFloat("Seed", &seedValue)) {
            Mod::get()->setSavedValue("seed-value", seedValue);
        }
        ImGui::Spacing();
        if (ImGui::Checkbox("Frame Stepper", &framestepEnabled)) {
            Mod::get()->setSavedValue("frame-stepper-enabled", framestepEnabled);
        }
        ImGui::Spacing();
        if (ImGui::Checkbox("Show Layout", &layoutEnabled)) {
            Mod::get()->setSavedValue("layout-mode-enabled", layoutEnabled);
        }
        ImGui::Spacing();
        if (ImGui::Checkbox("Show Hitboxes", &showHitboxes)) {
            Mod::get()->setSavedValue("show-hitboxes", showHitboxes);
        }
=======
        ImGui::Checkbox("Show Hitboxes", &showHitboxes);
        ImGui::Spacing();
        if (ImGui::Checkbox("Noclip", &noclipEnabled)) {
            Mod::get()->setSavedValue("noclip-enabled", noclipEnabled);
        }
        ImGui::SameLine();
        if (ImGui::Button("Players")) {
            ImGui::OpenPopup("NoclipPlayersPopup");
        }
        if (ImGui::BeginPopup("NoclipPlayersPopup")) {
            if (ImGui::Checkbox("Player 1", &noclipP1)) {
                Mod::get()->setSavedValue("noclip-p1", noclipP1);
            }
            if (ImGui::Checkbox("Player 2", &noclipP2)) {
                Mod::get()->setSavedValue("noclip-p2", noclipP2);
            }
            ImGui::EndPopup();
        }
        ImGui::Checkbox("Speedhack Enabled", &speedhackEnabled);
        ImGui::SameLine();
        ImGui::InputFloat("Speedhack", &speedhackMultiplier);
        if (speedhackMultiplier <= 0.f) {
            speedhackMultiplier = 1.0f;
        }
        ImGui::Checkbox("Seed Hack Enabled", &seedHackEnabled);
        ImGui::SameLine();
        ImGui::InputFloat("Seed", &seedValue);
>>>>>>> Stashed changes
    }    
    void renderHacksTab()
    {
        ImGui::Columns(2, "HacksColumns", false); 
        ImGui::SetColumnWidth(0, 200.0f);
        ImGui::SetColumnWidth(1, 200.0f);
        
        ImGui::Text("Respawn Time");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(80.0f);
        if (ImGui::InputFloat("##RespawnDelay", &respawnDelay)) {
            if (respawnDelay < 0.f) {
                respawnDelay = 1.f;
            } else if (respawnDelay > 2.f){
                respawnDelay = 1.f;
            }
            Mod::get()->setSavedValue<float>("respawn-delay", respawnDelay);
        }
        ImGui::Spacing();
        if (ImGui::Checkbox("Safe Mode", &safeMode)) {
            Mod::get()->setSavedValue("safe-mode", safeMode);
        }
        ImGui::NextColumn();
        
        if (ImGui::Checkbox("No Death Effect", &noDeathEffect)) {
            Mod::get()->setSavedValue("no-death-effect", noDeathEffect);
        }
        if (ImGui::Checkbox("No Respawn Flash", &noRespawnFlash)) {
            Mod::get()->setSavedValue("no-respawn-flash", noRespawnFlash);
        }
        if (ImGui::Checkbox("No Ghost Trail", &ghostTrail)) {
            updateGhostTrail();
            Mod::get()->setSavedValue("ghost-trail", ghostTrail);
        }
        if (ImGui::Checkbox("No Orb Effects", &noOrbEffectEnabled)) {
            Mod::get()->setSavedValue("no-orb-effects", noOrbEffectEnabled);
        }
        ImGui::SameLine();
        
        if (ImGui::Button("Effects")) {
            ImGui::OpenPopup("OrbEffectsPopup");
        }
        
        if (ImGui::BeginPopup("OrbEffectsPopup")) {
            if (ImGui::Checkbox("No Orb Ring", &noOrbRing)) {
                Mod::get()->setSavedValue("no-orb-ring", noOrbRing);
            }
            if (ImGui::Checkbox("No Orb Hit Effect", &noOrbHitEffect)) {
                Mod::get()->setSavedValue("no-orb-hit-effect", noOrbHitEffect);
            }
            if (ImGui::Checkbox("No Dash Boom", &noDashBoom)) {
                Mod::get()->setSavedValue("no-dash-boom", noDashBoom);
            }
            ImGui::EndPopup();
        }
        
        ImGui::Spacing();
        if (ImGui::Checkbox("No Dash Fire", &noDashFire)) {
            Mod::get()->setSavedValue("no-dash-fire", noDashFire);
        }
        if (ImGui::Checkbox("No Shaders", &noShaders)) {
            Mod::get()->setSavedValue("no-shaders", noShaders);
        }
        if (ImGui::Checkbox("No Mirror", &noMirror)) {
            Mod::get()->setSavedValue("no-mirror", noMirror);
        }
        if (ImGui::Checkbox("Instant Mirror", &instantMirror)) {
            Mod::get()->setSavedValue("instant-mirror", instantMirror);
        }
        if (ImGui::Checkbox("Keep Wave On", &keepWaveEnabled)) {
            Mod::get()->setSavedValue("keep-wave-on", keepWaveEnabled);
        }
        ImGui::Columns(1);
        ImGui::Separator();
        if (ImGui::Checkbox("Unlock Everything", &unlockEverything)) {
            Mod::get()->setSavedValue("unlock-everything", unlockEverything);
        }
        if (ImGui::Checkbox("Accurate Percentage", &accuratePercentage)) {
            Mod::get()->setSavedValue("accurate-percentage", accuratePercentage);
        }
        ImGui::SameLine();
        ImGui::InputInt("##DecimalPlaces", &decimalPlaces);
        if (decimalPlaces < 0) {
            decimalPlaces = 1;
        } else if (decimalPlaces > 20){
            decimalPlaces = 1;
        }
        
    }
    void renderAssists()
    {
        
    }
    void renderAutoclicker() 
    {
        ImGui::Checkbox("Autoclicker Enable", &autoClickerEnabled);
        
        if (autoClickerEnabled) {
            ImGui::Separator();
            
            ImGui::Text("Player 1 Controls:");
            
            // W Key
            if (ImGui::CollapsingHeader("W Key (Player 1 Jump)")) {
                ImGui::Indent();
                ImGui::Checkbox("Enable##W", &autoClick_W_enabled);
                if (autoClick_W_enabled) {
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Hold Frames##W", &autoClick_W_intervalHold);
                    if (autoClick_W_intervalHold < 0) autoClick_W_intervalHold = 0;
                    ImGui::SameLine(); ImGui::Text("(0 = infinite hold)");
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##W", &autoClick_W_intervalRelease);
                    if (autoClick_W_intervalRelease < 1) autoClick_W_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##W", &autoClick_W_clicksPerFrame);
                    if (autoClick_W_clicksPerFrame < 1) autoClick_W_clicksPerFrame = 1;
                    
                    ImGui::Checkbox("Swift Click##W", &autoClick_W_swiftClick);
                    ImGui::Checkbox("Limit Frames##W", &autoClick_W_limitFrames);
                    if (autoClick_W_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##W", &autoClick_W_maxFrames);
                        if (autoClick_W_maxFrames < 0) autoClick_W_maxFrames = 0;
                    }
                    
                    ImGui::Separator();
                    ImGui::Checkbox("Black Orb Mode##W", &autoClick_W_blackOrbModeEnabled);
                    if (autoClick_W_blackOrbModeEnabled) {
                        ImGui::Indent();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Click Count##W", &autoClick_W_blackOrb_clickCount);
                        if (autoClick_W_blackOrb_clickCount < 1) autoClick_W_blackOrb_clickCount = 1;
                        
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Hold Frames##W_BlackOrb", &autoClick_W_blackOrb_holdFrames);
                        if (autoClick_W_blackOrb_holdFrames < 1) autoClick_W_blackOrb_holdFrames = 1;
                        ImGui::Unindent();
                    }
                }
                ImGui::Unindent();
            }
            
            // A Key
            if (ImGui::CollapsingHeader("A Key (Player 1 Left)")) {
                ImGui::Indent();
                ImGui::Checkbox("Enable##A", &autoClick_A_enabled);
                if (autoClick_A_enabled) {
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Hold Frames##A", &autoClick_A_intervalHold);
                    if (autoClick_A_intervalHold < 0) autoClick_A_intervalHold = 0;
                    ImGui::SameLine(); ImGui::Text("(0 = infinite hold)");
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##A", &autoClick_A_intervalRelease);
                    if (autoClick_A_intervalRelease < 1) autoClick_A_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##A", &autoClick_A_clicksPerFrame);
                    if (autoClick_A_clicksPerFrame < 1) autoClick_A_clicksPerFrame = 1;
                    
                    ImGui::Checkbox("Swift Click##A", &autoClick_A_swiftClick);
                    ImGui::Checkbox("Limit Frames##A", &autoClick_A_limitFrames);
                    if (autoClick_A_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##A", &autoClick_A_maxFrames);
                        if (autoClick_A_maxFrames < 0) autoClick_A_maxFrames = 0;
                    }
                    
                    ImGui::Separator();
                    ImGui::Checkbox("Black Orb Mode##A", &autoClick_A_blackOrbModeEnabled);
                    if (autoClick_A_blackOrbModeEnabled) {
                        ImGui::Indent();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Click Count##A", &autoClick_A_blackOrb_clickCount);
                        if (autoClick_A_blackOrb_clickCount < 1) autoClick_A_blackOrb_clickCount = 1;
                        
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Hold Frames##A_BlackOrb", &autoClick_A_blackOrb_holdFrames);
                        if (autoClick_A_blackOrb_holdFrames < 1) autoClick_A_blackOrb_holdFrames = 1;
                        ImGui::Unindent();
                    }
                }
                ImGui::Unindent();
            }
            
            // D Key
            if (ImGui::CollapsingHeader("D Key (Player 1 Right)")) {
                ImGui::Indent();
                ImGui::Checkbox("Enable##D", &autoClick_D_enabled);
                if (autoClick_D_enabled) {
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Hold Frames##D", &autoClick_D_intervalHold);
                    if (autoClick_D_intervalHold < 0) autoClick_D_intervalHold = 0;
                    ImGui::SameLine(); ImGui::Text("(0 = infinite hold)");
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##D", &autoClick_D_intervalRelease);
                    if (autoClick_D_intervalRelease < 1) autoClick_D_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##D", &autoClick_D_clicksPerFrame);
                    if (autoClick_D_clicksPerFrame < 1) autoClick_D_clicksPerFrame = 1;
                    
                    ImGui::Checkbox("Swift Click##D", &autoClick_D_swiftClick);
                    ImGui::Checkbox("Limit Frames##D", &autoClick_D_limitFrames);
                    if (autoClick_D_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##D", &autoClick_D_maxFrames);
                        if (autoClick_D_maxFrames < 0) autoClick_D_maxFrames = 0;
                    }
                    
                    ImGui::Separator();
                    ImGui::Checkbox("Black Orb Mode##D", &autoClick_D_blackOrbModeEnabled);
                    if (autoClick_D_blackOrbModeEnabled) {
                        ImGui::Indent();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Click Count##D", &autoClick_D_blackOrb_clickCount);
                        if (autoClick_D_blackOrb_clickCount < 1) autoClick_D_blackOrb_clickCount = 1;
                        
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Hold Frames##D_BlackOrb", &autoClick_D_blackOrb_holdFrames);
                        if (autoClick_D_blackOrb_holdFrames < 1) autoClick_D_blackOrb_holdFrames = 1;
                        ImGui::Unindent();
                    }
                }
                ImGui::Unindent();
            }
            
            // SPACE Key
            if (ImGui::CollapsingHeader("SPACE Key (Player 1 Jump Alt)")) {
                ImGui::Indent();
                ImGui::Checkbox("Enable##SPACE", &autoClick_SPACE_enabled);
                if (autoClick_SPACE_enabled) {
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Hold Frames##SPACE", &autoClick_SPACE_intervalHold);
                    if (autoClick_SPACE_intervalHold < 0) autoClick_SPACE_intervalHold = 0;
                    ImGui::SameLine(); ImGui::Text("(0 = infinite hold)");
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##SPACE", &autoClick_SPACE_intervalRelease);
                    if (autoClick_SPACE_intervalRelease < 1) autoClick_SPACE_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##SPACE", &autoClick_SPACE_clicksPerFrame);
                    if (autoClick_SPACE_clicksPerFrame < 1) autoClick_SPACE_clicksPerFrame = 1;
                    
                    ImGui::Checkbox("Swift Click##SPACE", &autoClick_SPACE_swiftClick);
                    ImGui::Checkbox("Limit Frames##SPACE", &autoClick_SPACE_limitFrames);
                    if (autoClick_SPACE_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##SPACE", &autoClick_SPACE_maxFrames);
                        if (autoClick_SPACE_maxFrames < 0) autoClick_SPACE_maxFrames = 0;
                    }
                    
                    ImGui::Separator();
                    ImGui::Checkbox("Black Orb Mode##SPACE", &autoClick_SPACE_blackOrbModeEnabled);
                    if (autoClick_SPACE_blackOrbModeEnabled) {
                        ImGui::Indent();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Click Count##SPACE", &autoClick_SPACE_blackOrb_clickCount);
                        if (autoClick_SPACE_blackOrb_clickCount < 1) autoClick_SPACE_blackOrb_clickCount = 1;
                        
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Hold Frames##SPACE_BlackOrb", &autoClick_SPACE_blackOrb_holdFrames);
                        if (autoClick_SPACE_blackOrb_holdFrames < 1) autoClick_SPACE_blackOrb_holdFrames = 1;
                        ImGui::Unindent();
                    }
                }
                ImGui::Unindent();
            }
            
            ImGui::Separator();
            ImGui::Text("Player 2 Controls:");
            
            // UP Key
            if (ImGui::CollapsingHeader("UP Key (Player 2 Jump)")) {
                ImGui::Indent();
                ImGui::Checkbox("Enable##UP", &autoClick_UP_enabled);
                if (autoClick_UP_enabled) {
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Hold Frames##UP", &autoClick_UP_intervalHold);
                    if (autoClick_UP_intervalHold < 0) autoClick_UP_intervalHold = 0;
                    ImGui::SameLine(); ImGui::Text("(0 = infinite hold)");
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##UP", &autoClick_UP_intervalRelease);
                    if (autoClick_UP_intervalRelease < 1) autoClick_UP_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##UP", &autoClick_UP_clicksPerFrame);
                    if (autoClick_UP_clicksPerFrame < 1) autoClick_UP_clicksPerFrame = 1;
                    
                    ImGui::Checkbox("Swift Click##UP", &autoClick_UP_swiftClick);
                    ImGui::Checkbox("Limit Frames##UP", &autoClick_UP_limitFrames);
                    if (autoClick_UP_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##UP", &autoClick_UP_maxFrames);
                        if (autoClick_UP_maxFrames < 0) autoClick_UP_maxFrames = 0;
                    }
                    
                    ImGui::Separator();
                    ImGui::Checkbox("Black Orb Mode##UP", &autoClick_UP_blackOrbModeEnabled);
                    if (autoClick_UP_blackOrbModeEnabled) {
                        ImGui::Indent();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Click Count##UP", &autoClick_UP_blackOrb_clickCount);
                        if (autoClick_UP_blackOrb_clickCount < 1) autoClick_UP_blackOrb_clickCount = 1;
                        
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Hold Frames##UP_BlackOrb", &autoClick_UP_blackOrb_holdFrames);
                        if (autoClick_UP_blackOrb_holdFrames < 1) autoClick_UP_blackOrb_holdFrames = 1;
                        ImGui::Unindent();
                    }
                }
                ImGui::Unindent();
            }
            
            // LEFT Key
            if (ImGui::CollapsingHeader("LEFT Key (Player 2 Left)")) {
                ImGui::Indent();
                ImGui::Checkbox("Enable##LEFT", &autoClick_LEFT_enabled);
                if (autoClick_LEFT_enabled) {
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Hold Frames##LEFT", &autoClick_LEFT_intervalHold);
                    if (autoClick_LEFT_intervalHold < 0) autoClick_LEFT_intervalHold = 0;
                    ImGui::SameLine(); ImGui::Text("(0 = infinite hold)");
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##LEFT", &autoClick_LEFT_intervalRelease);
                    if (autoClick_LEFT_intervalRelease < 1) autoClick_LEFT_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##LEFT", &autoClick_LEFT_clicksPerFrame);
                    if (autoClick_LEFT_clicksPerFrame < 1) autoClick_LEFT_clicksPerFrame = 1;
                    
                    ImGui::Checkbox("Swift Click##LEFT", &autoClick_LEFT_swiftClick);
                    ImGui::Checkbox("Limit Frames##LEFT", &autoClick_LEFT_limitFrames);
                    if (autoClick_LEFT_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##LEFT", &autoClick_LEFT_maxFrames);
                        if (autoClick_LEFT_maxFrames < 0) autoClick_LEFT_maxFrames = 0;
                    }
                    
                    ImGui::Separator();
                    ImGui::Checkbox("Black Orb Mode##LEFT", &autoClick_LEFT_blackOrbModeEnabled);
                    if (autoClick_LEFT_blackOrbModeEnabled) {
                        ImGui::Indent();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Click Count##LEFT", &autoClick_LEFT_blackOrb_clickCount);
                        if (autoClick_LEFT_blackOrb_clickCount < 1) autoClick_LEFT_blackOrb_clickCount = 1;
                        
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Hold Frames##LEFT_BlackOrb", &autoClick_LEFT_blackOrb_holdFrames);
                        if (autoClick_LEFT_blackOrb_holdFrames < 1) autoClick_LEFT_blackOrb_holdFrames = 1;
                        ImGui::Unindent();
                    }
                }
                ImGui::Unindent();
            }
            
            // RIGHT Key
            if (ImGui::CollapsingHeader("RIGHT Key (Player 2 Right)")) {
                ImGui::Indent();
                ImGui::Checkbox("Enable##RIGHT", &autoClick_RIGHT_enabled);
                if (autoClick_RIGHT_enabled) {
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Hold Frames##RIGHT", &autoClick_RIGHT_intervalHold);
                    if (autoClick_RIGHT_intervalHold < 0) autoClick_RIGHT_intervalHold = 0;
                    ImGui::SameLine(); ImGui::Text("(0 = infinite hold)");
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##RIGHT", &autoClick_RIGHT_intervalRelease);
                    if (autoClick_RIGHT_intervalRelease < 1) autoClick_RIGHT_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##RIGHT", &autoClick_RIGHT_clicksPerFrame);
                    if (autoClick_RIGHT_clicksPerFrame < 1) autoClick_RIGHT_clicksPerFrame = 1;
                    
                    ImGui::Checkbox("Swift Click##RIGHT", &autoClick_RIGHT_swiftClick);
                    ImGui::Checkbox("Limit Frames##RIGHT", &autoClick_RIGHT_limitFrames);
                    if (autoClick_RIGHT_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##RIGHT", &autoClick_RIGHT_maxFrames);
                        if (autoClick_RIGHT_maxFrames < 0) autoClick_RIGHT_maxFrames = 0;
                    }
                    
                    ImGui::Separator();
                    ImGui::Checkbox("Black Orb Mode##RIGHT", &autoClick_RIGHT_blackOrbModeEnabled);
                    if (autoClick_RIGHT_blackOrbModeEnabled) {
                        ImGui::Indent();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Click Count##RIGHT", &autoClick_RIGHT_blackOrb_clickCount);
                        if (autoClick_RIGHT_blackOrb_clickCount < 1) autoClick_RIGHT_blackOrb_clickCount = 1;
                        
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Hold Frames##RIGHT_BlackOrb", &autoClick_RIGHT_blackOrb_holdFrames);
                        if (autoClick_RIGHT_blackOrb_holdFrames < 1) autoClick_RIGHT_blackOrb_holdFrames = 1;
                        ImGui::Unindent();
                    }
                }
                ImGui::Unindent();
            }
            
            ImGui::Separator();
            
            if (ImGui::Button("Disable All")) {
                autoClick_W_enabled = false;
                autoClick_A_enabled = false;
                autoClick_D_enabled = false;
                autoClick_UP_enabled = false;
                autoClick_LEFT_enabled = false;
                autoClick_RIGHT_enabled = false;
                autoClick_SPACE_enabled = false;
            }
            
            ImGui::SameLine();
            if (ImGui::Button("Enable All Jump Keys")) {
                autoClick_W_enabled = true;
                autoClick_UP_enabled = true;
                autoClick_SPACE_enabled = true;
            }
            
            ImGui::SameLine();
            if (ImGui::Button("Enable All Movement")) {
                autoClick_A_enabled = true;
                autoClick_D_enabled = true;
                autoClick_LEFT_enabled = true;
                autoClick_RIGHT_enabled = true;
            }
        }
    }
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
        if (!ImGui::Begin("Astral [BETA]", nullptr, flags)) {
            ImGui::End();
            return;
        }
        
        float width = ImGui::GetContentRegionAvail().x;
        const char* title = "Astral [BETA]";
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
        ImGui::Text("Frame: %.2f", frameCount);
        
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