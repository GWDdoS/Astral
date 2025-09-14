#include "includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

const char* tabNames[] = {"Botting", "Hacks", "Autoclicker", "Render", "Settings", "Customization", "Mod Updates"};
const int tabCount = 7;

int currentTab = 0;
float themeColor[3] = {0.4f, 0.4f, 0.4f}; // Greyscale theme
static bool styleApplied = false;
static bool guiVisible = false;

// Animation and visual effects variables
static float animationTime = 0.0f;
static std::vector<ImVec2> stars;
static std::vector<float> starBrightness;
static std::vector<float> starTwinkleSpeed;
static const int NUM_STARS = 150;
static bool starsInitialized = false;
static ImTextureID logoTexture = nullptr;

#ifdef GEODE_IS_DESKTOP

// Initialize starfield
void initializeStarfield() {
    if (starsInitialized) return;
    
    stars.clear();
    starBrightness.clear();
    starTwinkleSpeed.clear();
    
    // Generate random stars
    for (int i = 0; i < NUM_STARS; i++) {
        stars.push_back(ImVec2(
            static_cast<float>(rand()) / RAND_MAX * 800.0f, // Random X position
            static_cast<float>(rand()) / RAND_MAX * 600.0f  // Random Y position
        ));
        starBrightness.push_back(static_cast<float>(rand()) / RAND_MAX);
        starTwinkleSpeed.push_back(0.5f + static_cast<float>(rand()) / RAND_MAX * 2.0f);
    }
    starsInitialized = true;
}

void updateStarfield(float deltaTime) {
    animationTime += deltaTime;
    
    for (int i = 0; i < stars.size(); i++) {
        // Update star twinkling
        starBrightness[i] = 0.3f + 0.7f * (sin(animationTime * starTwinkleSpeed[i]) * 0.5f + 0.5f);
        
        // Slowly move stars
        stars[i].x += sin(animationTime * 0.1f + i) * 0.1f;
        stars[i].y += cos(animationTime * 0.1f + i) * 0.1f;
        
        // Wrap stars around screen
        if (stars[i].x > 800.0f) stars[i].x = 0.0f;
        if (stars[i].x < 0.0f) stars[i].x = 800.0f;
        if (stars[i].y > 600.0f) stars[i].y = 0.0f;
        if (stars[i].y < 0.0f) stars[i].y = 600.0f;
    }
}

void drawStarfield(ImDrawList* drawList, ImVec2 windowPos, ImVec2 windowSize) {
    // Draw dark galaxy background
    ImU32 bgColor1 = IM_COL32(5, 8, 15, 255);   // Very dark blue
    ImU32 bgColor2 = IM_COL32(15, 15, 25, 255); // Slightly lighter
    
    // Gradient background
    drawList->AddRectFilledMultiColor(
        windowPos,
        ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y),
        bgColor1, bgColor2, bgColor2, bgColor1
    );
    
    // Draw twinkling stars
    for (int i = 0; i < stars.size(); i++) {
        ImVec2 starPos = ImVec2(windowPos.x + stars[i].x * windowSize.x / 800.0f, 
                               windowPos.y + stars[i].y * windowSize.y / 600.0f);
        
        // Only draw stars within window bounds
        if (starPos.x >= windowPos.x && starPos.x <= windowPos.x + windowSize.x &&
            starPos.y >= windowPos.y && starPos.y <= windowPos.y + windowSize.y) {
            
            float brightness = starBrightness[i];
            ImU32 starColor = IM_COL32(
                static_cast<int>(200 * brightness),
                static_cast<int>(220 * brightness),
                static_cast<int>(255 * brightness),
                static_cast<int>(255 * brightness)
            );
            
            // Draw star with slight glow effect
            drawList->AddCircleFilled(starPos, 1.0f + brightness * 0.5f, starColor);
            
            // Add subtle glow for brighter stars
            if (brightness > 0.7f) {
                ImU32 glowColor = IM_COL32(
                    static_cast<int>(100 * (brightness - 0.7f)),
                    static_cast<int>(150 * (brightness - 0.7f)),
                    static_cast<int>(200 * (brightness - 0.7f)),
                    static_cast<int>(50 * (brightness - 0.7f))
                );
                drawList->AddCircleFilled(starPos, 3.0f, glowColor);
            }
        }
    }
}

void setupImGuiStyle() {
    auto& style = ImGui::GetStyle();
    auto& io = ImGui::GetIO();
    
    // Load font
    auto* font = io.Fonts->AddFontFromFileTTF(
        (Mod::get()->getResourcesDir() / ("font" + std::to_string(0) + ".ttf")).string().c_str(), 16.0f
    );
    
    // Greyscale dark theme
    style.Alpha = 0.95f;
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
    
    // Greyscale color scheme
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text]                   = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.12f, 0.15f, 0.94f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.15f, 0.17f, 0.20f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.12f, 0.14f, 0.17f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.30f, 0.35f, 0.40f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.20f, 0.22f, 0.25f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.30f, 0.32f, 0.35f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.35f, 0.37f, 0.40f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.08f, 0.10f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.15f, 0.17f, 0.20f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.12f, 0.14f, 0.17f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.33f, 0.36f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.43f, 0.46f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.53f, 0.56f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.70f, 0.72f, 0.75f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.40f, 0.42f, 0.45f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.60f, 0.62f, 0.65f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.25f, 0.27f, 0.30f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.35f, 0.37f, 0.40f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.45f, 0.47f, 0.50f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.30f, 0.32f, 0.35f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.40f, 0.42f, 0.45f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.50f, 0.52f, 0.55f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.45f, 0.48f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.53f, 0.55f, 0.58f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.63f, 0.65f, 0.68f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.40f, 0.42f, 0.45f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.50f, 0.52f, 0.55f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.60f, 0.62f, 0.65f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.20f, 0.22f, 0.25f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.40f, 0.42f, 0.45f, 0.80f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.35f, 0.37f, 0.40f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.15f, 0.17f, 0.20f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.25f, 0.27f, 0.30f, 1.00f);
    
    styleApplied = true;
    initializeStarfield();
}

// Enhanced button with animation
bool animatedButton(const char* label, const ImVec2& size = ImVec2(0, 0)) {
    ImVec2 pos = ImGui::GetCursorScreenPos();
    bool clicked = ImGui::Button(label, size);
    
    if (ImGui::IsItemHovered()) {
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 buttonSize = ImGui::GetItemRectSize();
        
        // Animated glow effect
        float pulse = sin(animationTime * 3.0f) * 0.5f + 0.5f;
        ImU32 glowColor = IM_COL32(150, 150, 150, static_cast<int>(50 * pulse));
        
        drawList->AddRect(
            ImVec2(pos.x - 2, pos.y - 2),
            ImVec2(pos.x + buttonSize.x + 2, pos.y + buttonSize.y + 2),
            glowColor, 8.0f, 0, 2.0f
        );
    }
    
    return clicked;
}

void renderBottingTab() {
    ImGui::InputFloat("TPS Value:", &tpsValue);
    if (tpsValue < 0.f) {
        tpsValue = 240.f;
    }
    
    if (animatedButton("Record Macro", ImVec2(150, 30))) {}
    ImGui::SameLine();
    if (animatedButton("Play Macro", ImVec2(150, 30))) {}
    
    ImGui::Spacing();
    ImGui::Text("Macro Settings:");
    
    // Animated separator
    ImGui::Separator();
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    float pulse = sin(animationTime * 2.0f) * 0.3f + 0.7f;
    drawList->AddLine(
        ImVec2(pos.x, pos.y - 10),
        ImVec2(pos.x + ImGui::GetContentRegionAvail().x, pos.y - 10),
        IM_COL32(100, 100, 100, static_cast<int>(255 * pulse)),
        1.0f
    );
}

void renderHacksTab() {
    ImGui::Checkbox("Noclip", &noclipEnabled);
    ImGui::SameLine();
    if (ImGui::BeginMenu("  ")) {
        ImGui::Checkbox("Player 1", &noclipP1);
        ImGui::Checkbox("Player 2", &noclipP2);
        ImGui::EndMenu();
    }
    
    ImGui::Spacing();
    ImGui::Checkbox("Speedhack", &speedhackEnabled);
    ImGui::SameLine();
    ImGui::InputFloat(" ", &speedhackMultiplier);
    if (speedhackMultiplier < 0.f) {
        speedhackMultiplier = 1.f;
    }
    
    ImGui::Spacing();
    ImGui::Checkbox("Safe Mode", &safeMode);
    ImGui::Spacing();
    ImGui::Checkbox("No Death Effect", &noDeathEffect);
    ImGui::Spacing();
    ImGui::Checkbox("No Respawn Flash", &noRespawnFlash);
    ImGui::Spacing();
    ImGui::Checkbox("No Shaders", &noShaders);
    ImGui::Spacing();
    ImGui::Checkbox("No Mirror", &noMirror);
    ImGui::Spacing();
    ImGui::Checkbox("Instant Mirror", &instantMirror);
    ImGui::Spacing();
    
    ImGui::InputFloat("Respawn Delay", &respawnDelay);
    if (respawnDelay != 0.f && respawnDelay != 2.f) {
        respawnDelay = (fabs(respawnDelay - 0.f) < fabs(respawnDelay - 2.f)) ? 0.f : 2.f;
    }
    
    ImGui::Spacing();
    ImGui::Checkbox("Show Trajectory", &trajectoryEnabled);
    ImGui::Spacing();
    ImGui::Checkbox("Frame Stepper", &framestepEnabled);
}

void renderAutoClickerTab() {
    ImGui::Text("Auto Clicker Settings");
    ImGui::Separator();
    
    // Placeholder for autoclicker functionality
    ImGui::TextDisabled("Coming Soon...");
}

void renderRenderTab() {
    ImGui::Checkbox("Show Layout", &layoutEnabled);
    
    if (animatedButton("Start Render", ImVec2(150, 30))) {}
    ImGui::SameLine();
    if (animatedButton("Stop Render", ImVec2(150, 30))) {}
    
    ImGui::Spacing();
    ImGui::Checkbox("Show Hitboxes", &showHitboxes);
    ImGui::Checkbox("Show Grid", &showGrid);
}

void renderSettingsTab() {
    ImGui::Text("Toggle GUI Key:");
    
    const char* currentKeyDisplay = getKeyName(capturedCustomKey);
    if (animatedButton(isCapturingKeybind ? "Press any key..." : currentKeyDisplay, ImVec2(120, 25))) {
        isCapturingKeybind = true;
    }
    
    if (isCapturingKeybind) {
        ImGui::SameLine();
        if (animatedButton("Cancel")) {
            isCapturingKeybind = false;
        }
    }
    
    ImGui::Text("Current Key: %s", currentKeyDisplay);
}

void renderCustomizationTab() {
    ImGui::Text("Theme Color (Greyscale):");
    ImGui::ColorEdit3("##accentcolor", themeColor);
    
    // Force greyscale
    float avg = (themeColor[0] + themeColor[1] + themeColor[2]) / 3.0f;
    themeColor[0] = themeColor[1] = themeColor[2] = avg;
}

void renderTodoTab() {
    ImGui::BulletText("Enhanced UI with animated starfield background");
    ImGui::BulletText("Greyscale theme implementation");
    ImGui::BulletText("Logo integration in top-left corner");
    ImGui::BulletText("Smooth animations and visual effects");
    ImGui::BulletText("Improved button interactions");
}

void renderMainGui() {
    if (!ImGui::GetCurrentContext()) return;
    
    auto& imguiCocos = ImGuiCocos::get();
    if (&imguiCocos == nullptr) return;
    
    guiVisible = imguiCocos.isVisible();
    if (tabCount <= 0) return;
    
    // Update animations
    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
    lastTime = currentTime;
    
    updateStarfield(deltaTime);
    
    // Main window setup
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | 
                            ImGuiWindowFlags_AlwaysAutoResize | 
                            ImGuiWindowFlags_NoResize | 
                            ImGuiWindowFlags_NoTitleBar;
    
    ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
    
    if (!ImGui::Begin("Astral [BETA]", nullptr, flags)) {
        ImGui::End();
        return;
    }
    
    // Get window properties for background rendering
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    
    // Draw animated starfield background
    drawStarfield(drawList, windowPos, windowSize);
    
    // Logo in top-left (placeholder - you'd load actual texture)
    ImVec2 logoPos = ImVec2(windowPos.x + 15, windowPos.y + 15);
    ImVec2 logoSize = ImVec2(32, 32);
    
    if (logoTexture != 0) {
        drawList->AddImage(logoTexture, logoPos, ImVec2(logoPos.x + logoSize.x, logoPos.y + logoSize.y));
    } else {
        // Placeholder logo (simple geometric shape)
        drawList->AddCircleFilled(ImVec2(logoPos.x + 16, logoPos.y + 16), 16, IM_COL32(200, 200, 200, 255));
        drawList->AddText(ImVec2(logoPos.x + 8, logoPos.y + 8), IM_COL32(50, 50, 50, 255), "A");
    }
    
    // Title with offset to accommodate logo
    ImGui::SetCursorPosX(60); // Offset for logo
    ImGui::SetCursorPosY(25);
    
    const char* title = "Astral [BETA]";
    ImGui::Text("%s", title);
    
    // Animated title underline
    ImVec2 titlePos = ImGui::GetCursorScreenPos();
    float titleWidth = ImGui::CalcTextSize(title).x;
    float pulse = sin(animationTime * 1.5f) * 0.3f + 0.7f;
    drawList->AddLine(
        ImVec2(titlePos.x - 60, titlePos.y),
        ImVec2(titlePos.x - 60 + titleWidth, titlePos.y),
        IM_COL32(150, 150, 150, static_cast<int>(255 * pulse)),
        2.0f
    );
    
    ImGui::Separator();
    ImGui::SetCursorPosY(70);
    
    // Tab buttons with enhanced styling
    for (int i = 0; i < tabCount; i++) {
        if (!tabNames[i]) continue;
        
        // Highlight current tab
        if (i == currentTab) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.45f, 0.47f, 0.50f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.55f, 0.57f, 0.60f, 1.0f));
        }
        
        if (animatedButton(tabNames[i])) {
            currentTab = i;
        }
        
        if (i == currentTab) {
            ImGui::PopStyleColor(2);
        }
        
        if (i < tabCount - 1) ImGui::SameLine();
    }
    
    ImGui::Separator();
    
    // Render current tab content
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

#endif

#ifdef GEODE_IS_MOBILE
// Mobile Cocos GUI
class $modify(MenuLayer) {
    void onMoreGames(CCObject* target) {
        Astral_GUI_Mobile_UI::create()->show();
    }
};
#endif