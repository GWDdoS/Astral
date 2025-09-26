#pragma once

// Bools
extern bool recording;
extern bool replaying;
extern bool rendering;
extern bool noclipP1;
extern bool noclipP2;
extern bool shouldNoclip;
extern bool noclipEnabled;
extern bool layoutEnabled;
extern bool oldphysEnabled;
extern bool trajectoryEnabled;
extern bool styleApplied;
extern bool guiVisible;
extern bool framestepEnabled;
extern bool lockedDeltaEnabled;
extern bool speedhackEnabled;
extern bool speedhackAudio;
extern bool isCapturingKeybind;
extern bool showHitboxes;
extern bool showGrid;
extern bool currentGuiState;
extern bool safeMode;
extern bool noDeathEffect;
extern bool noRespawnFlash;
extern bool tpsEnabled;
extern bool noShaders;
extern bool noMirror;
extern bool instantMirror;
extern bool keepWaveEnabled;
extern bool autoSafeMode;
extern bool initialized;
extern bool forceSafeMode;
extern bool unlockEverything;
extern bool seedHackEnabled;
extern bool accuratePercentage;
extern bool autoClickerEnabled;
extern bool bool fpsEnabled;

// Floats
extern float tpsValue;
extern float themeColor[3];
extern float speedhackMultiplier;
extern float lockedDeltaValue;
extern float currentPitch;
extern float currentSpeedValue;
extern float speedValue;
extern float respawnDelay;
extern float frameCount;
extern float fpsValue;

// Ints
extern int selectedKeybind;
extern int selectedTheme;
extern int backgroundTheme;
extern int inputMerge;
extern int fontList;
extern int fontType;
extern int currentTab;
extern int decimalPlaces;
extern int seedValue;

// IDK
extern const int backgroundThemeNamesCount;
extern const int tabCount;

// Chars
extern char macroName[128];
extern const char* backgroundThemeNames[];
extern const char* tabNames[];
extern const char* getKeyName(cocos2d::enumKeyCodes keyCode);
extern const char* currentKeyDisplay;

// Something
extern cocos2d::enumKeyCodes capturedCustomKey;

// Autoclicker
#define DECL_AUTOKEY(NAME) \
extern bool autoClick_##NAME##_enabled; \
extern int  autoClick_##NAME##_intervalHold; \
extern int  autoClick_##NAME##_intervalRelease; \
extern int  autoClick_##NAME##_clicksPerFrame; \
extern bool autoClick_##NAME##_swiftClick; \
extern bool autoClick_##NAME##_limitFrames; \
extern int  autoClick_##NAME##_maxFrames; \
extern bool autoClick_##NAME##_blackOrbModeEnabled; \
extern int  autoClick_##NAME##_blackOrb_clickCount; \
extern int  autoClick_##NAME##_blackOrb_holdFrames;

DECL_AUTOKEY(W)
DECL_AUTOKEY(A)
DECL_AUTOKEY(D)
DECL_AUTOKEY(UP)
DECL_AUTOKEY(LEFT)
DECL_AUTOKEY(RIGHT)
DECL_AUTOKEY(SPACE)