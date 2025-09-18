#include "../../includes.hpp"

// i was told this would be easier than just setting up a massive line of bools and shit
struct AutoClickerSettings {
    bool enabled = false;
    int intervalHold = 1;
    int intervalRelease = 1;
    int clicksPerFrame = 1;
    bool swiftClick = false;
    bool limitFrames = false;
    int maxFrames = 0;
};

bool autoClickerEnabled = false;
AutoClickerSettings autoClick_W;
AutoClickerSettings autoClick_A;
AutoClickerSettings autoClick_S;
AutoClickerSettings autoClick_UP;
AutoClickerSettings autoClick_LEFT;
AutoClickerSettings autoClick_RIGHT;
AutoClickerSettings autoClick_SPACE;

class $modify(GJBaseGameLayer) {
    struct Fields {
        struct ClickerState {
            int timer = 0;
            bool clicking = false;
            int framesClicked = 0;
        };
        ClickerState w_state, a_state, s_state, up_state, left_state, right_state, space_state;
    };
    
    void handleAutoClick(AutoClickerSettings& settings, Fields::ClickerState& state, int buttonType, bool isPlayer1 = true) {
        if (!settings.enabled) return;
        
        if (settings.limitFrames && state.framesClicked >= settings.maxFrames && settings.maxFrames > 0) {
            return;
        }
        
        state.timer++;
        
        bool shouldToggle = false;
        if (!state.clicking && state.timer >= settings.intervalHold) {
            shouldToggle = true;
        } else if (state.clicking && state.timer >= settings.intervalRelease) {
            shouldToggle = true;
        }
        
        if (shouldToggle) {
            state.clicking = !state.clicking;
            
            for (int i = 0; i < settings.clicksPerFrame; i++) {
                this->handleButton(state.clicking, buttonType, isPlayer1);
                
                if (settings.swiftClick && state.clicking) {
                    this->handleButton(false, buttonType, isPlayer1);
                }
            }
            
            state.timer = 0;
            if (settings.limitFrames) {
                state.framesClicked++;
            }
        }
    }
    
    void processCommands(float dt) {
        GJBaseGameLayer::processCommands(dt);
        
        if (!autoClickerEnabled || !PlayLayer::get()) return;
        
        // swift click
        handleAutoClick(autoClick_W, m_fields->w_state, static_cast<int>(PlayerButton::Jump));
        handleAutoClick(autoClick_A, m_fields->a_state, static_cast<int>(PlayerButton::Left));
        handleAutoClick(autoClick_S, m_fields->s_state, static_cast<int>(PlayerButton::Down));
        handleAutoClick(autoClick_UP, m_fields->up_state, static_cast<int>(PlayerButton::Jump));
        handleAutoClick(autoClick_LEFT, m_fields->left_state, static_cast<int>(PlayerButton::Left));
        handleAutoClick(autoClick_RIGHT, m_fields->right_state, static_cast<int>(PlayerButton::Right));
        handleAutoClick(autoClick_SPACE, m_fields->space_state, static_cast<int>(PlayerButton::Jump));
    }
};