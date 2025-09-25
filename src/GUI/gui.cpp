#include "includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

const char* tabNames[] = {"Botting", "Hacks", "Assists", "Autoclicker" "Render", "Settings"};
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
        
        // Update last progress for next frame
        lastProgress = currentProgress;
        
        return frameCount;
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
        // this should make a text box.
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
        ImGui::InputFloat("##Seed", seedValue);
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
                    if (autoClick_W_intervalHold < 1) autoClick_W_intervalHold = 1;
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##W", &autoClick_W_intervalRelease);
                    if (autoClick_W_intervalRelease < 1) autoClick_W_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##W", &autoClick_W_clicksPerFrame);
                    if (autoClick_W_clicksPerFrame < 1) autoClick_W_clicksPerFrame = 1;
                    if (autoClick_W_clicksPerFrame > 10) autoClick_W_clicksPerFrame = 10;
                    
                    ImGui::Checkbox("Swift Click##W", &autoClick_W_swiftClick);
                    ImGui::Checkbox("Limit Frames##W", &autoClick_W_limitFrames);
                    if (autoClick_W_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##W", &autoClick_W_maxFrames);
                        if (autoClick_W_maxFrames < 0) autoClick_W_maxFrames = 0;
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
                    if (autoClick_A_intervalHold < 1) autoClick_A_intervalHold = 1;
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##A", &autoClick_A_intervalRelease);
                    if (autoClick_A_intervalRelease < 1) autoClick_A_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##A", &autoClick_A_clicksPerFrame);
                    if (autoClick_A_clicksPerFrame < 1) autoClick_A_clicksPerFrame = 1;
                    if (autoClick_A_clicksPerFrame > 10) autoClick_A_clicksPerFrame = 10;
                    
                    ImGui::Checkbox("Swift Click##A", &autoClick_A_swiftClick);
                    ImGui::Checkbox("Limit Frames##A", &autoClick_A_limitFrames);
                    if (autoClick_A_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##A", &autoClick_A_maxFrames);
                        if (autoClick_A_maxFrames < 0) autoClick_A_maxFrames = 0;
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
                    if (autoClick_D_intervalHold < 1) autoClick_D_intervalHold = 1;
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##D", &autoClick_D_intervalRelease);
                    if (autoClick_D_intervalRelease < 1) autoClick_D_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##D", &autoClick_D_clicksPerFrame);
                    if (autoClick_D_clicksPerFrame < 1) autoClick_D_clicksPerFrame = 1;
                    if (autoClick_D_clicksPerFrame > 10) autoClick_D_clicksPerFrame = 10;
                    
                    ImGui::Checkbox("Swift Click##D", &autoClick_D_swiftClick);
                    ImGui::Checkbox("Limit Frames##D", &autoClick_D_limitFrames);
                    if (autoClick_D_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##D", &autoClick_D_maxFrames);
                        if (autoClick_D_maxFrames < 0) autoClick_D_maxFrames = 0;
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
                    if (autoClick_SPACE_intervalHold < 1) autoClick_SPACE_intervalHold = 1;
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##SPACE", &autoClick_SPACE_intervalRelease);
                    if (autoClick_SPACE_intervalRelease < 1) autoClick_SPACE_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##SPACE", &autoClick_SPACE_clicksPerFrame);
                    if (autoClick_SPACE_clicksPerFrame < 1) autoClick_SPACE_clicksPerFrame = 1;
                    if (autoClick_SPACE_clicksPerFrame > 10) autoClick_SPACE_clicksPerFrame = 10;
                    
                    ImGui::Checkbox("Swift Click##SPACE", &autoClick_SPACE_swiftClick);
                    ImGui::Checkbox("Limit Frames##SPACE", &autoClick_SPACE_limitFrames);
                    if (autoClick_SPACE_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##SPACE", &autoClick_SPACE_maxFrames);
                        if (autoClick_SPACE_maxFrames < 0) autoClick_SPACE_maxFrames = 0;
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
                    if (autoClick_UP_intervalHold < 1) autoClick_UP_intervalHold = 1;
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##UP", &autoClick_UP_intervalRelease);
                    if (autoClick_UP_intervalRelease < 1) autoClick_UP_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##UP", &autoClick_UP_clicksPerFrame);
                    if (autoClick_UP_clicksPerFrame < 1) autoClick_UP_clicksPerFrame = 1;
                    if (autoClick_UP_clicksPerFrame > 10) autoClick_UP_clicksPerFrame = 10;
                    
                    ImGui::Checkbox("Swift Click##UP", &autoClick_UP_swiftClick);
                    ImGui::Checkbox("Limit Frames##UP", &autoClick_UP_limitFrames);
                    if (autoClick_UP_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##UP", &autoClick_UP_maxFrames);
                        if (autoClick_UP_maxFrames < 0) autoClick_UP_maxFrames = 0;
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
                    if (autoClick_LEFT_intervalHold < 1) autoClick_LEFT_intervalHold = 1;
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##LEFT", &autoClick_LEFT_intervalRelease);
                    if (autoClick_LEFT_intervalRelease < 1) autoClick_LEFT_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##LEFT", &autoClick_LEFT_clicksPerFrame);
                    if (autoClick_LEFT_clicksPerFrame < 1) autoClick_LEFT_clicksPerFrame = 1;
                    if (autoClick_LEFT_clicksPerFrame > 10) autoClick_LEFT_clicksPerFrame = 10;
                    
                    ImGui::Checkbox("Swift Click##LEFT", &autoClick_LEFT_swiftClick);
                    ImGui::Checkbox("Limit Frames##LEFT", &autoClick_LEFT_limitFrames);
                    if (autoClick_LEFT_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##LEFT", &autoClick_LEFT_maxFrames);
                        if (autoClick_LEFT_maxFrames < 0) autoClick_LEFT_maxFrames = 0;
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
                    if (autoClick_RIGHT_intervalHold < 1) autoClick_RIGHT_intervalHold = 1;
                    
                    ImGui::SetNextItemWidth(100);
                    ImGui::InputInt("Release Frames##RIGHT", &autoClick_RIGHT_intervalRelease);
                    if (autoClick_RIGHT_intervalRelease < 1) autoClick_RIGHT_intervalRelease = 1;
                    
                    ImGui::SetNextItemWidth(80);
                    ImGui::InputInt("Clicks/Frame##RIGHT", &autoClick_RIGHT_clicksPerFrame);
                    if (autoClick_RIGHT_clicksPerFrame < 1) autoClick_RIGHT_clicksPerFrame = 1;
                    if (autoClick_RIGHT_clicksPerFrame > 10) autoClick_RIGHT_clicksPerFrame = 10;
                    
                    ImGui::Checkbox("Swift Click##RIGHT", &autoClick_RIGHT_swiftClick);
                    ImGui::Checkbox("Limit Frames##RIGHT", &autoClick_RIGHT_limitFrames);
                    if (autoClick_RIGHT_limitFrames) {
                        ImGui::SameLine();
                        ImGui::SetNextItemWidth(80);
                        ImGui::InputInt("Max Frames##RIGHT", &autoClick_RIGHT_maxFrames);
                        if (autoClick_RIGHT_maxFrames < 0) autoClick_RIGHT_maxFrames = 0;
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
    // this should do the Mobile Cocos GUI
    class $modify(MenuLayer) {
        void onMoreGames(CCObject* target) {
            Astral_GUI_Mobile_UI::create()->show();
        }
    };
    #endif