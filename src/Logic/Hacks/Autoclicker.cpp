#include "../../includes.hpp"

bool autoClickerEnabled = false;

// Define key settings - intervalHold of 0 means infinite hold
#define DEFINE_KEY_SETTINGS(KEY) \
bool autoClick_##KEY##_enabled = false; \
int autoClick_##KEY##_intervalHold = 1; \
int autoClick_##KEY##_intervalRelease = 1; \
int autoClick_##KEY##_clicksPerFrame = 1; \
bool autoClick_##KEY##_swiftClick = false; \
bool autoClick_##KEY##_limitFrames = false; \
int autoClick_##KEY##_maxFrames = 0; \
bool autoClick_##KEY##_blackOrbModeEnabled = false; \
int autoClick_##KEY##_blackOrb_clickCount = 1; \
int autoClick_##KEY##_blackOrb_holdFrames = 1;

DEFINE_KEY_SETTINGS(W)
DEFINE_KEY_SETTINGS(A)
DEFINE_KEY_SETTINGS(D)
DEFINE_KEY_SETTINGS(UP)
DEFINE_KEY_SETTINGS(LEFT)
DEFINE_KEY_SETTINGS(RIGHT)
DEFINE_KEY_SETTINGS(SPACE)

#ifdef GEODE_IS_DESKTOP
class $modify(GJBaseGameLayer) {
    struct Fields {
        struct KeyState {
            int timer = 0;
            bool clicking = false;
            int framesClicked = 0;
            int orbFrame = 0;
            bool initialized = false;
        };
        KeyState keyW, keyA, keyD, keyUP, keyLEFT, keyRIGHT, keySPACE;
    };
    
    void processKey(Fields::KeyState& state,
        bool enabled, bool limitFrames, int maxFrames,
        int intervalHold, int intervalRelease,
        int clicksPerFrame, bool swiftClick,
        bool blackOrbEnabled, int orbClickCount, int orbHoldFrames,
        PlayerButton button, bool isPlayer1)
        {
            if (!enabled) {
                if (state.clicking) {
                    this->handleButton(false, static_cast<int>(button), isPlayer1);
                    state.clicking = false;
                }
                state.initialized = false;
                return;
            }
            
            if (!state.initialized) {
                state.timer = 0;
                state.clicking = false;
                state.framesClicked = 0;
                state.orbFrame = 0;
                state.initialized = true;
            }
            
            if (limitFrames && state.framesClicked >= maxFrames && maxFrames > 0) {
                if (state.clicking) {
                    this->handleButton(false, static_cast<int>(button), isPlayer1);
                    state.clicking = false;
                }
                return;
            }
            
            // Hold mode - intervalHold of 0 means infinite hold
            if (intervalHold == 0) {
                if (!state.clicking) {
                    this->handleButton(true, static_cast<int>(button), isPlayer1);
                    state.clicking = true;
                    if (limitFrames) state.framesClicked++;
                }
                return;
            }
            /*
            Frame Structure
            Frame 1: Click X time + Start holding (Y)
            Frame 2: Release hold + Click once
            Frame 3: Wait for Y frames (should be hold number)
            Frame 4: Click X time + Start holding (cycle repeats)
            */
           /*
            if (blackOrbEnabled) {
                if (state.orbFrame == 0) {
                    // Frame 1: Click X times AND start holding
                    for (int i = 0; i < orbClickCount; i++) {
                        this->handleButton(true, static_cast<int>(button), isPlayer1);
                        this->handleButton(false, static_cast<int>(button), isPlayer1);
                    }
                    // Then start holding
                    this->handleButton(true, static_cast<int>(button), isPlayer1);
                    state.clicking = true;
                    state.orbFrame++;
                } else if (state.orbFrame <= orbHoldFrames) {
                    // Frame 2+: Continue holding for Y frames, then release and click once on the last frame
                    if (state.orbFrame == orbHoldFrames) {
                        // Release the hold
                        this->handleButton(false, static_cast<int>(button), isPlayer1);
                        // Do one more click
                        this->handleButton(true, static_cast<int>(button), isPlayer1);
                        this->handleButton(false, static_cast<int>(button), isPlayer1);
                        state.clicking = false;
                    }
                    state.orbFrame++;
                } else if (state.orbFrame <= orbHoldFrames + orbHoldFrames) {
                    // Wait frames - do nothing
                    state.orbFrame++;
                } else {
                    // Reset cycle
                    state.orbFrame = 0;
                    if (limitFrames) state.framesClicked++;
                }
                return;
            }
            */
            state.timer++;
            bool shouldToggle = false;
            
            if (!state.clicking && state.timer >= intervalHold) {
                shouldToggle = true;
            } else if (state.clicking && state.timer >= intervalRelease) {
                shouldToggle = true;
            }
            
            if (shouldToggle) {
                state.clicking = !state.clicking;
                
                if (state.clicking) {
                    for (int i = 0; i < clicksPerFrame; i++) {
                        this->handleButton(true, static_cast<int>(button), isPlayer1);
                        
                        if (swiftClick) {
                            this->handleButton(false, static_cast<int>(button), isPlayer1);
                        }
                    }
                    
                    if (!swiftClick) {
                    }
                    if (limitFrames) state.framesClicked++;
                } else {
                    if (!swiftClick) {
                        this->handleButton(false, static_cast<int>(button), isPlayer1);
                    }
                }
                
                state.timer = 0;
            }
        }
        
        void update(float dt) {
            GJBaseGameLayer::update(dt);
            
            if (!autoClickerEnabled || !PlayLayer::get()) return;
            
            processKey(m_fields->keyW, 
                autoClick_W_enabled, autoClick_W_limitFrames, autoClick_W_maxFrames,
                autoClick_W_intervalHold, autoClick_W_intervalRelease, autoClick_W_clicksPerFrame,
                autoClick_W_swiftClick, autoClick_W_blackOrbModeEnabled,
                autoClick_W_blackOrb_clickCount, autoClick_W_blackOrb_holdFrames,
                PlayerButton::Jump, true);
                
                processKey(m_fields->keyA, 
                    autoClick_A_enabled, autoClick_A_limitFrames, autoClick_A_maxFrames,
                    autoClick_A_intervalHold, autoClick_A_intervalRelease, autoClick_A_clicksPerFrame,
                    autoClick_A_swiftClick, autoClick_A_blackOrbModeEnabled,
                    autoClick_A_blackOrb_clickCount, autoClick_A_blackOrb_holdFrames,
                    PlayerButton::Left, true);
                    
                    processKey(m_fields->keyD, 
                        autoClick_D_enabled, autoClick_D_limitFrames, autoClick_D_maxFrames,
                        autoClick_D_intervalHold, autoClick_D_intervalRelease, autoClick_D_clicksPerFrame,
                        autoClick_D_swiftClick, autoClick_D_blackOrbModeEnabled,
                        autoClick_D_blackOrb_clickCount, autoClick_D_blackOrb_holdFrames,
                        PlayerButton::Right, true);
                        
                        processKey(m_fields->keyUP, 
                            autoClick_UP_enabled, autoClick_UP_limitFrames, autoClick_UP_maxFrames,
                            autoClick_UP_intervalHold, autoClick_UP_intervalRelease, autoClick_UP_clicksPerFrame,
                            autoClick_UP_swiftClick, autoClick_UP_blackOrbModeEnabled,
                            autoClick_UP_blackOrb_clickCount, autoClick_UP_blackOrb_holdFrames,
                            PlayerButton::Jump, false);
                            
                            processKey(m_fields->keyLEFT, 
                                autoClick_LEFT_enabled, autoClick_LEFT_limitFrames, autoClick_LEFT_maxFrames,
                                autoClick_LEFT_intervalHold, autoClick_LEFT_intervalRelease, autoClick_LEFT_clicksPerFrame,
                                autoClick_LEFT_swiftClick, autoClick_LEFT_blackOrbModeEnabled,
                                autoClick_LEFT_blackOrb_clickCount, autoClick_LEFT_blackOrb_holdFrames,
                                PlayerButton::Left, false);
                                
                                processKey(m_fields->keyRIGHT, 
                                    autoClick_RIGHT_enabled, autoClick_RIGHT_limitFrames, autoClick_RIGHT_maxFrames,
                                    autoClick_RIGHT_intervalHold, autoClick_RIGHT_intervalRelease, autoClick_RIGHT_clicksPerFrame,
                                    autoClick_RIGHT_swiftClick, autoClick_RIGHT_blackOrbModeEnabled,
                                    autoClick_RIGHT_blackOrb_clickCount, autoClick_RIGHT_blackOrb_holdFrames,
                                    PlayerButton::Right, false);
                                    
                                    processKey(m_fields->keySPACE, 
                                        autoClick_SPACE_enabled, autoClick_SPACE_limitFrames, autoClick_SPACE_maxFrames,
                                        autoClick_SPACE_intervalHold, autoClick_SPACE_intervalRelease, autoClick_SPACE_clicksPerFrame,
                                        autoClick_SPACE_swiftClick, autoClick_SPACE_blackOrbModeEnabled,
                                        autoClick_SPACE_blackOrb_clickCount, autoClick_SPACE_blackOrb_holdFrames,
                                        PlayerButton::Jump, true);
                                    }
                                };
                                #endif