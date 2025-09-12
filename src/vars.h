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