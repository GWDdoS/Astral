#include "includes.hpp"

using namespace geode::prelude;

const char* getKeyName(cocos2d::enumKeyCodes keyCode);

const char* tabNames[] = {"Botting", "Hacks", "Autoclicker", "Render", "Settings", "Customization", "Mod Updates"};
const int tabCount = 7;

int currentTab = 0;
float themeColor[3] = {0.4f, 0.4f, 0.4f}; // Greyscale theme

// File-local variables (if only used in this file)
static bool styleApplied = false;
static bool guiVisible = false;

#ifdef GEODE_IS_DESKTOP

// Animation and visual effects variables - declared at file scope
static float animationTime = 0.0f;
static std::vector<ImVec2> stars;
static std::vector<float> starBrightness;
static std::vector<float> starTwinkleSpeed;
static std::vector<float> starSize;
static std::vector<float> starGlowIntensity;
static const int NUM_STARS = 200;
static bool starsInitialized = false;

// Initialize starfield
void initializeStarfield() {
    if (starsInitialized) return;
    
    stars.clear();
    starBrightness.clear();
    starTwinkleSpeed.clear();
    starSize.clear();
    starGlowIntensity.clear();
    
    // Generate galaxy-like formation of stars
    ImVec2 galaxyCenter = ImVec2(400.0f, 300.0f); // Center of galaxy
    float galaxyWidth = 600.0f;
    float galaxyHeight = 100.0f;
    
    for (int i = 0; i < NUM_STARS; i++) {
        // Create galaxy spiral/line formation
        float t = static_cast<float>(i) / NUM_STARS;
        float angle = t * 6.28f * 2.0f; // Two full rotations for spiral
        float distance = t * 200.0f + (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 50.0f;
        
        // Create galaxy arm position
        float spiralX = galaxyCenter.x + cos(angle) * distance * 0.8f + (static_cast<float>(rand()) / RAND_MAX - 0.5f) * galaxyWidth * 0.3f;
        float spiralY = galaxyCenter.y + sin(angle) * distance * 0.2f + (static_cast<float>(rand()) / RAND_MAX - 0.5f) * galaxyHeight;
        
        stars.push_back(ImVec2(spiralX, spiralY));
        
        // Varied brightness (denser areas are brighter)
        float densityFactor = 1.0f - (distance / 200.0f); // Closer to center = brighter
        starBrightness.push_back(0.2f + densityFactor * 0.6f + static_cast<float>(rand()) / RAND_MAX * 0.2f);
        
        // Slower, varied twinkle speeds
        starTwinkleSpeed.push_back(0.1f + static_cast<float>(rand()) / RAND_MAX * 0.3f);
        
        // Different star sizes (bigger stars in center)
        starSize.push_back(0.5f + densityFactor * 1.5f + static_cast<float>(rand()) / RAND_MAX * 1.0f);
        
        // Glow intensity based on size and brightness
        starGlowIntensity.push_back(densityFactor * 0.8f + static_cast<float>(rand()) / RAND_MAX * 0.4f);
    }
    starsInitialized = true;
}

void updateStarfield(float deltaTime) {
    animationTime += deltaTime;
    
    for (size_t i = 0; i < stars.size(); i++) {
        // Update star twinkling (much slower)
        starBrightness[i] = 0.3f + 0.7f * (sin(animationTime * starTwinkleSpeed[i]) * 0.5f + 0.5f);
        
        // Very slow galaxy rotation and drift
        float rotationSpeed = 0.005f; // Much slower rotation
        float centerX = 400.0f;
        float centerY = 300.0f;
        
        // Rotate stars very slowly around galaxy center
        float dx = stars[i].x - centerX;
        float dy = stars[i].y - centerY;
        float newAngle = atan2(dy, dx) + rotationSpeed * deltaTime;
        float distance = sqrt(dx * dx + dy * dy);
        
        stars[i].x = centerX + cos(newAngle) * distance;
        stars[i].y = centerY + sin(newAngle) * distance;
        
        // Add very subtle drift
        stars[i].x += sin(animationTime * 0.01f + i) * 0.02f;
        stars[i].y += cos(animationTime * 0.008f + i) * 0.02f;
        
        // Wrap stars around screen bounds
        if (stars[i].x > 1000.0f) stars[i].x = -100.0f;
        if (stars[i].x < -100.0f) stars[i].x = 1000.0f;
        if (stars[i].y > 700.0f) stars[i].y = -100.0f;
        if (stars[i].y < -100.0f) stars[i].y = 700.0f;
    }
}

void drawStarfield(ImDrawList* drawList, ImVec2 windowPos, ImVec2 windowSize) {
    // No background - just transparent/default ImGui background
    
    // Draw galaxy stars with varied sizes and glow
    for (size_t i = 0; i < stars.size(); i++) {
        ImVec2 starPos = ImVec2(windowPos.x + stars[i].x * windowSize.x / 800.0f, 
                               windowPos.y + stars[i].y * windowSize.y / 600.0f);
        
        // Only draw stars within window bounds
        if (starPos.x >= windowPos.x - 50 && starPos.x <= windowPos.x + windowSize.x + 50 &&
            starPos.y >= windowPos.y - 50 && starPos.y <= windowPos.y + windowSize.y + 50) {
            
            float brightness = starBrightness[i];
            float size = starSize[i];
            float glowIntensity = starGlowIntensity[i];
            
            // Main star color - bright white/blue
            ImU32 starColor = IM_COL32(
                static_cast<int>(240 * brightness),
                static_cast<int>(250 * brightness),
                static_cast<int>(255 * brightness),
                static_cast<int>(255 * brightness)
            );
            
            // Draw main star
            drawList->AddCircleFilled(starPos, size, starColor);
            
            // Add glow effects for larger/brighter stars
            if (glowIntensity > 0.3f) {
                // Inner glow
                ImU32 innerGlowColor = IM_COL32(
                    static_cast<int>(200 * glowIntensity),
                    static_cast<int>(220 * glowIntensity),
                    static_cast<int>(255 * glowIntensity),
                    static_cast<int>(80 * glowIntensity)
                );
                drawList->AddCircleFilled(starPos, size * 2.0f, innerGlowColor);
                
                // Outer glow for very bright stars
                if (glowIntensity > 0.6f) {
                    ImU32 outerGlowColor = IM_COL32(
                        static_cast<int>(150 * glowIntensity),
                        static_cast<int>(180 * glowIntensity),
                        static_cast<int>(255 * glowIntensity),
                        static_cast<int>(40 * glowIntensity)
                    );
                    drawList->AddCircleFilled(starPos, size * 4.0f, outerGlowColor);
                }
                
                // Star flare effect for the brightest stars
                if (glowIntensity > 0.8f && size > 1.5f) {
                    ImU32 flareColor = IM_COL32(
                        static_cast<int>(255 * brightness),
                        static_cast<int>(255 * brightness),
                        static_cast<int>(255 * brightness),
                        static_cast<int>(60 * brightness)
                    );
                    
                    // Horizontal flare
                    drawList->AddLine(
                        ImVec2(starPos.x - size * 6, starPos.y),
                        ImVec2(starPos.x + size * 6, starPos.y),
                        flareColor, 1.0f
                    );
                    
                    // Vertical flare
                    drawList->AddLine(
                        ImVec2(starPos.x, starPos.y - size * 6),
                        ImVec2(starPos.x, starPos.y + size * 6),
                        flareColor, 1.0f
                    );
                }
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
    
    // Simple placeholder logo in top-left
    ImVec2 logoPos = ImVec2(windowPos.x + 15, windowPos.y + 15);
    drawList->AddCircleFilled(ImVec2(logoPos.x + 16, logoPos.y + 16), 16, IM_COL32(200, 200, 200, 255));
    drawList->AddText(ImVec2(logoPos.x + 8, logoPos.y + 8), IM_COL32(50, 50, 50, 255), "A");
    
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