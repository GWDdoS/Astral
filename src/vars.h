#pragma once

//Bools
extern bool recording;
extern bool replaying;
extern bool rendering;
extern bool noclipP1;
extern bool noclipP2;
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

//Floats
extern float seedValue;
extern float tpsValue;
extern float themeColor[3];
extern float speedValue;
extern float lockedDeltaValue;
extern float currentPitch;
extern float currentSpeedValue;
extern float speedValue;

//Ints
extern int selectedKeybind;
extern int selectedTheme;
extern int noclipMode;
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