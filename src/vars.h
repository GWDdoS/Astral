#pragma once

//Bools
extern bool recording;
extern bool replaying;
extern bool rendering;
extern bool noclipP1;
extern bool noclipP2;
extern bool shouldNoclip;
extern bool noclipEnabled;
// extern bool noclipEnabled;
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
extern bool framestepEnabled;
extern bool keepWaveEnabled;
extern bool autoSafeMode;
extern bool initialized;
extern bool forceSafeMode;
extern bool framestepEnabled;

//Floats
extern float seedValue;
extern float tpsValue;
extern float themeColor[3];
extern float speedhackMultiplier;
extern float lockedDeltaValue;
extern float currentPitch;
extern float currentSpeedValue;
extern float speedValue;
extern float respawnDelay;
extern float frameCount;

//Ints
extern int selectedKeybind;
extern int selectedTheme;
extern int backgroundTheme;
extern int inputMerge;
extern const int backgroundThemeNamesCount;
extern int fontList;
extern int fontType;
extern int currentTab;
extern const int tabCount;

//Chars
extern char macroName[128];
extern const char *backgroundThemeNames[];
extern const char* tabNames[];
extern const char* getKeyName(cocos2d::enumKeyCodes keyCode);
extern const char* currentKeyDisplay;

// Other
extern cocos2d::enumKeyCodes capturedCustomKey;

extern bool autoClickerEnabled;

// W Key
extern bool autoClick_W_enabled;
extern int autoClick_W_intervalHold;
extern int autoClick_W_intervalRelease;
extern int autoClick_W_clicksPerFrame;
extern bool autoClick_W_swiftClick;
extern bool autoClick_W_limitFrames;
extern int autoClick_W_maxFrames;

// A Key
extern bool autoClick_A_enabled;
extern int autoClick_A_intervalHold;
extern int autoClick_A_intervalRelease;
extern int autoClick_A_clicksPerFrame;
extern bool autoClick_A_swiftClick;
extern bool autoClick_A_limitFrames;
extern int autoClick_A_maxFrames;

// D Key
extern bool autoClick_D_enabled;
extern int autoClick_D_intervalHold;
extern int autoClick_D_intervalRelease;
extern int autoClick_D_clicksPerFrame;
extern bool autoClick_D_swiftClick;
extern bool autoClick_D_limitFrames;
extern int autoClick_D_maxFrames;

// UP Key
extern bool autoClick_UP_enabled;
extern int autoClick_UP_intervalHold;
extern int autoClick_UP_intervalRelease;
extern int autoClick_UP_clicksPerFrame;
extern bool autoClick_UP_swiftClick;
extern bool autoClick_UP_limitFrames;
extern int autoClick_UP_maxFrames;

// LEFT Key
extern bool autoClick_LEFT_enabled;
extern int autoClick_LEFT_intervalHold;
extern int autoClick_LEFT_intervalRelease;
extern int autoClick_LEFT_clicksPerFrame;
extern bool autoClick_LEFT_swiftClick;
extern bool autoClick_LEFT_limitFrames;
extern int autoClick_LEFT_maxFrames;

// RIGHT Key
extern bool autoClick_RIGHT_enabled;
extern int autoClick_RIGHT_intervalHold;
extern int autoClick_RIGHT_intervalRelease;
extern int autoClick_RIGHT_clicksPerFrame;
extern bool autoClick_RIGHT_swiftClick;
extern bool autoClick_RIGHT_limitFrames;
extern int autoClick_RIGHT_maxFrames;

// SPACE Key
extern bool autoClick_SPACE_enabled;
extern int autoClick_SPACE_intervalHold;
extern int autoClick_SPACE_intervalRelease;
extern int autoClick_SPACE_clicksPerFrame;
extern bool autoClick_SPACE_swiftClick;
extern bool autoClick_SPACE_limitFrames;
extern int autoClick_SPACE_maxFrames;

