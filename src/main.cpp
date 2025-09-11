#include "includes.hpp"


using namespace geode::prelude;

/*
de3am is a boykisser and a list helper
Breuhh is also a boykisser and a list helper. (de3am told me to put this)
*/

// The unholy list of vars
// bools
bool noclipP1 = false;
bool noclipP2 = false;
bool noclipBoth = false;
bool noclipEnabled = false;
// bool noclipEnabled = false;
bool recording = false;
bool replaying = false;
bool rendering = false;
bool trajectoryEnabled = false;
bool layoutEnabled = false;
bool oldphysEnabled = false;
bool styleApplied = false;
bool framestepEnabled = false;
bool lockedDeltaEnabled = false;
bool guiVisible = false;
bool speedhackEnabled = false;
bool speedhackAudio = false;
bool isCapturingKeybind = false;
bool showHitboxes = false;
bool showGrid = false;
bool currentGuiState = false;
bool safeMode = false;
bool noDeathEffect = false;
bool noRespawnFlash = false;

// Floats
float seedValue = 1.0f;
float tpsValue = 240.0f;
float currentP = 1.0f;
float respawnDelay = 1.0f;

// Ints
int backgroundTheme = 0;
int inputMerge = 0;
int fontType = 0;
int fontList = 0;

// Chars
char macroName[128] = "Test";
const char* currentKeyDisplay = nullptr;

const char *backgroundThemeNames[] = {"Dark", "Light", "Medium"};
const int backgroundThemeNamesCount = sizeof(backgroundThemeNames) / sizeof(backgroundThemeNames[0]);


#ifdef GEODE_IS_MACOS
    cocos2d::enumKeyCodes capturedCustomKey = cocos2d::enumKeyCodes::KEY_Tab;
#endif
#ifdef GEODE_IS_WINDOWS
    cocos2d::enumKeyCodes capturedCustomKey = cocos2d::enumKeyCodes::KEY_Alt;
#endif



#ifdef GEODE_IS_WINDOWS
// Ai is good for one thing, making a fucking massive list :skull:
const char* getKeyName(cocos2d::enumKeyCodes keyCode) {
    switch(keyCode) {
        case cocos2d::enumKeyCodes::KEY_Alt: return "Alt";
        case cocos2d::enumKeyCodes::KEY_F1: return "F1";
        case cocos2d::enumKeyCodes::KEY_F2: return "F2";
        case cocos2d::enumKeyCodes::KEY_F3: return "F3";
        case cocos2d::enumKeyCodes::KEY_F4: return "F4";
        case cocos2d::enumKeyCodes::KEY_F5: return "F5";
        case cocos2d::enumKeyCodes::KEY_F6: return "F6";
        case cocos2d::enumKeyCodes::KEY_F7: return "F7";
        case cocos2d::enumKeyCodes::KEY_F8: return "F8";
        case cocos2d::enumKeyCodes::KEY_F9: return "F9";
        case cocos2d::enumKeyCodes::KEY_F10: return "F10";
        case cocos2d::enumKeyCodes::KEY_F11: return "F11";
        case cocos2d::enumKeyCodes::KEY_F12: return "F12";
        case cocos2d::enumKeyCodes::KEY_Insert: return "Insert";
        case cocos2d::enumKeyCodes::KEY_Home: return "Home";
        case cocos2d::enumKeyCodes::KEY_End: return "End";
        case cocos2d::enumKeyCodes::KEY_PageUp: return "Page Up";
        case cocos2d::enumKeyCodes::KEY_PageDown: return "Page Down";
        case cocos2d::enumKeyCodes::KEY_Delete: return "Delete";
        case cocos2d::enumKeyCodes::KEY_Space: return "Space";
        case cocos2d::enumKeyCodes::KEY_Enter: return "Enter";
        case cocos2d::enumKeyCodes::KEY_Escape: return "Escape";
        case cocos2d::enumKeyCodes::KEY_Tab: return "Tab";
        case cocos2d::enumKeyCodes::KEY_Shift: return "Shift";
        case cocos2d::enumKeyCodes::KEY_Control: return "Ctrl";
        case cocos2d::enumKeyCodes::KEY_ArrowLeft: return "Left Arrow";
        case cocos2d::enumKeyCodes::KEY_ArrowRight: return "Right Arrow";
        case cocos2d::enumKeyCodes::KEY_ArrowUp: return "Up Arrow";
        case cocos2d::enumKeyCodes::KEY_ArrowDown: return "Down Arrow";
        
        // Missing cases to add:
        case cocos2d::enumKeyCodes::KEY_None: return "None";
        case cocos2d::enumKeyCodes::KEY_Backspace: return "Backspace";
        case cocos2d::enumKeyCodes::KEY_Pause: return "Pause";
        case cocos2d::enumKeyCodes::KEY_CapsLock: return "Caps Lock";
        case cocos2d::enumKeyCodes::KEY_Select: return "Select";
        
        // Letter keys (A-Z)
        case cocos2d::enumKeyCodes::KEY_A: return "A";
        case cocos2d::enumKeyCodes::KEY_B: return "B";
        case cocos2d::enumKeyCodes::KEY_C: return "C";
        case cocos2d::enumKeyCodes::KEY_D: return "D";
        case cocos2d::enumKeyCodes::KEY_E: return "E";
        case cocos2d::enumKeyCodes::KEY_F: return "F";
        case cocos2d::enumKeyCodes::KEY_G: return "G";
        case cocos2d::enumKeyCodes::KEY_H: return "H";
        case cocos2d::enumKeyCodes::KEY_I: return "I";
        case cocos2d::enumKeyCodes::KEY_J: return "J";
        case cocos2d::enumKeyCodes::KEY_K: return "K";
        case cocos2d::enumKeyCodes::KEY_L: return "L";
        case cocos2d::enumKeyCodes::KEY_M: return "M";
        case cocos2d::enumKeyCodes::KEY_N: return "N";
        case cocos2d::enumKeyCodes::KEY_O: return "O";
        case cocos2d::enumKeyCodes::KEY_P: return "P";
        case cocos2d::enumKeyCodes::KEY_Q: return "Q";
        case cocos2d::enumKeyCodes::KEY_R: return "R";
        case cocos2d::enumKeyCodes::KEY_S: return "S";
        case cocos2d::enumKeyCodes::KEY_T: return "T";
        case cocos2d::enumKeyCodes::KEY_U: return "U";
        case cocos2d::enumKeyCodes::KEY_V: return "V";
        case cocos2d::enumKeyCodes::KEY_W: return "W";
        case cocos2d::enumKeyCodes::KEY_X: return "X";
        case cocos2d::enumKeyCodes::KEY_Y: return "Y";
        case cocos2d::enumKeyCodes::KEY_Z: return "Z";
        case cocos2d::enumKeyCodes::KEY_ScrollLock: return "Scroll Lock";
        
        default: return "Unknown Key";
    }
}
#endif
#ifdef GEODE_IS_MACOS
const char* getKeyName(cocos2d::enumKeyCodes keyCode) {
    switch(keyCode) {
        case cocos2d::enumKeyCodes::KEY_Alt: return "Option";
        case cocos2d::enumKeyCodes::KEY_F1: return "F1";
        case cocos2d::enumKeyCodes::KEY_F2: return "F2";
        case cocos2d::enumKeyCodes::KEY_F3: return "F3";
        case cocos2d::enumKeyCodes::KEY_F4: return "F4";
        case cocos2d::enumKeyCodes::KEY_F5: return "F5";
        case cocos2d::enumKeyCodes::KEY_F6: return "F6";
        case cocos2d::enumKeyCodes::KEY_F7: return "F7";
        case cocos2d::enumKeyCodes::KEY_F8: return "F8";
        case cocos2d::enumKeyCodes::KEY_F9: return "F9";
        case cocos2d::enumKeyCodes::KEY_F10: return "F10";
        case cocos2d::enumKeyCodes::KEY_F11: return "F11";
        case cocos2d::enumKeyCodes::KEY_F12: return "F12";
        case cocos2d::enumKeyCodes::KEY_Insert: return "Insert";
        case cocos2d::enumKeyCodes::KEY_Home: return "Home";
        case cocos2d::enumKeyCodes::KEY_End: return "End";
        case cocos2d::enumKeyCodes::KEY_PageUp: return "Page Up";
        case cocos2d::enumKeyCodes::KEY_PageDown: return "Page Down";
        case cocos2d::enumKeyCodes::KEY_Delete: return "Delete";
        case cocos2d::enumKeyCodes::KEY_Space: return "Space";
        case cocos2d::enumKeyCodes::KEY_Enter: return "Return";
        case cocos2d::enumKeyCodes::KEY_Escape: return "Escape";
        case cocos2d::enumKeyCodes::KEY_Tab: return "Tab";
        case cocos2d::enumKeyCodes::KEY_Shift: return "Shift";
        case cocos2d::enumKeyCodes::KEY_Control: return "Control";
        case cocos2d::enumKeyCodes::KEY_ArrowLeft: return "←";
        case cocos2d::enumKeyCodes::KEY_ArrowRight: return "→";
        case cocos2d::enumKeyCodes::KEY_ArrowUp: return "↑";
        case cocos2d::enumKeyCodes::KEY_ArrowDown: return "↓";
        
        case cocos2d::enumKeyCodes::KEY_None: return "None";
        case cocos2d::enumKeyCodes::KEY_Backspace: return "Delete";
        case cocos2d::enumKeyCodes::KEY_Pause: return "Pause";
        case cocos2d::enumKeyCodes::KEY_CapsLock: return "Caps Lock";
        case cocos2d::enumKeyCodes::KEY_Select: return "Select";
        
        // Letter keys (A-Z)
        case cocos2d::enumKeyCodes::KEY_A: return "A";
        case cocos2d::enumKeyCodes::KEY_B: return "B";
        case cocos2d::enumKeyCodes::KEY_C: return "C";
        case cocos2d::enumKeyCodes::KEY_D: return "D";
        case cocos2d::enumKeyCodes::KEY_E: return "E";
        case cocos2d::enumKeyCodes::KEY_F: return "F";
        case cocos2d::enumKeyCodes::KEY_G: return "G";
        case cocos2d::enumKeyCodes::KEY_H: return "H";
        case cocos2d::enumKeyCodes::KEY_I: return "I";
        case cocos2d::enumKeyCodes::KEY_J: return "J";
        case cocos2d::enumKeyCodes::KEY_K: return "K";
        case cocos2d::enumKeyCodes::KEY_L: return "L";
        case cocos2d::enumKeyCodes::KEY_M: return "M";
        case cocos2d::enumKeyCodes::KEY_N: return "N";
        case cocos2d::enumKeyCodes::KEY_O: return "O";
        case cocos2d::enumKeyCodes::KEY_P: return "P";
        case cocos2d::enumKeyCodes::KEY_Q: return "Q";
        case cocos2d::enumKeyCodes::KEY_R: return "R";
        case cocos2d::enumKeyCodes::KEY_S: return "S";
        case cocos2d::enumKeyCodes::KEY_T: return "T";
        case cocos2d::enumKeyCodes::KEY_U: return "U";
        case cocos2d::enumKeyCodes::KEY_V: return "V";
        case cocos2d::enumKeyCodes::KEY_W: return "W";
        case cocos2d::enumKeyCodes::KEY_X: return "X";
        case cocos2d::enumKeyCodes::KEY_Y: return "Y";
        case cocos2d::enumKeyCodes::KEY_Z: return "Z";
        case cocos2d::enumKeyCodes::KEY_ScrollLock: return "Scroll Lock";
        
        default: return "Unknown Key";
    }
}
#endif

$on_mod(Loaded)
{
    #ifndef GEODE_IS_MOBILE
    ImGuiCocos::get().setup([]
        {
            setupImGuiStyle();
        })
        .draw([]
            {
                renderMainGui();
            });
    #endif
        }
        
        class $modify(ImGuiKeybindHook, cocos2d::CCKeyboardDispatcher){
            bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat)
            {
                if (isCapturingKeybind && isKeyDown && !isKeyRepeat) {
                    if (key == cocos2d::enumKeyCodes::KEY_Escape) {
                        isCapturingKeybind = false;
                    } else {
                        capturedCustomKey = key;
                        isCapturingKeybind = false;
                    }
                    return true; 
                }
                
                if (capturedCustomKey != cocos2d::enumKeyCodes::KEY_None && key == capturedCustomKey && isKeyDown) {
                    ImGuiCocos::get().toggle();
                    guiVisible = ImGuiCocos::get().isVisible();
                }
                
                return cocos2d::CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
            }
        };
