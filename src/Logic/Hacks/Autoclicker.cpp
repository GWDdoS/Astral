#include "../../includes.hpp"

class $modify(GJBaseGameLayer) {
    struct Fields {
        // W Key state
        int w_timer = 0;
        bool w_clicking = false;
        int w_framesClicked = 0;
        
        // A Key state
        int a_timer = 0;
        bool a_clicking = false;
        int a_framesClicked = 0;
        
        // D Key state
        int d_timer = 0;
        bool d_clicking = false;
        int d_framesClicked = 0;
        
        // UP Key state
        int up_timer = 0;
        bool up_clicking = false;
        int up_framesClicked = 0;
        
        // LEFT Key state
        int left_timer = 0;
        bool left_clicking = false;
        int left_framesClicked = 0;
        
        // RIGHT Key state
        int right_timer = 0;
        bool right_clicking = false;
        int right_framesClicked = 0;
        
        // SPACE Key state
        int space_timer = 0;
        bool space_clicking = false;
        int space_framesClicked = 0;
    };
    
    void update(float dt) {
        GJBaseGameLayer::update(dt);  // Call original update first
        
        if (!autoClickerEnabled || !PlayLayer::get()) return;
        
        // W Key autoclicker
        if (autoClick_W_enabled) {
            if (autoClick_W_limitFrames && m_fields->w_framesClicked >= autoClick_W_maxFrames && autoClick_W_maxFrames > 0) {
                // Do nothing
            } else {
                m_fields->w_timer++;
                bool shouldToggle = false;
                if (!m_fields->w_clicking && m_fields->w_timer >= autoClick_W_intervalHold) {
                    shouldToggle = true;
                } else if (m_fields->w_clicking && m_fields->w_timer >= autoClick_W_intervalRelease) {
                    shouldToggle = true;
                }
                if (shouldToggle) {
                    m_fields->w_clicking = !m_fields->w_clicking;
                    for (int i = 0; i < autoClick_W_clicksPerFrame; i++) {
                        this->handleButton(m_fields->w_clicking, static_cast<int>(PlayerButton::Jump), true);
                        if (autoClick_W_swiftClick && m_fields->w_clicking) {
                            this->handleButton(false, static_cast<int>(PlayerButton::Jump), true);
                        }
                    }
                    m_fields->w_timer = 0;
                    if (autoClick_W_limitFrames) {
                        m_fields->w_framesClicked++;
                    }
                }
            }
        }
        
        // A Key autoclicker (Player 1 Left)
        if (autoClick_A_enabled) {
            if (autoClick_A_limitFrames && m_fields->a_framesClicked >= autoClick_A_maxFrames && autoClick_A_maxFrames > 0) {
                // Do nothing
            } else {
                m_fields->a_timer++;
                bool shouldToggle = false;
                if (!m_fields->a_clicking && m_fields->a_timer >= autoClick_A_intervalHold) {
                    shouldToggle = true;
                } else if (m_fields->a_clicking && m_fields->a_timer >= autoClick_A_intervalRelease) {
                    shouldToggle = true;
                }
                if (shouldToggle) {
                    m_fields->a_clicking = !m_fields->a_clicking;
                    for (int i = 0; i < autoClick_A_clicksPerFrame; i++) {
                        this->handleButton(m_fields->a_clicking, static_cast<int>(PlayerButton::Left), true); // Player 1 Left
                        if (autoClick_A_swiftClick && m_fields->a_clicking) {
                            this->handleButton(false, static_cast<int>(PlayerButton::Left), true);
                        }
                    }
                    m_fields->a_timer = 0;
                    if (autoClick_A_limitFrames) {
                        m_fields->a_framesClicked++;
                    }
                }
            }
        }
        
        // D Key autoclicker (Player 1 Right)
        if (autoClick_D_enabled) {
            if (autoClick_D_limitFrames && m_fields->d_framesClicked >= autoClick_D_maxFrames && autoClick_D_maxFrames > 0) {
                // Do nothing
            } else {
                m_fields->d_timer++;
                bool shouldToggle = false;
                if (!m_fields->d_clicking && m_fields->d_timer >= autoClick_D_intervalHold) {
                    shouldToggle = true;
                } else if (m_fields->d_clicking && m_fields->d_timer >= autoClick_D_intervalRelease) {
                    shouldToggle = true;
                }
                if (shouldToggle) {
                    m_fields->d_clicking = !m_fields->d_clicking;
                    for (int i = 0; i < autoClick_D_clicksPerFrame; i++) {
                        this->handleButton(m_fields->d_clicking, static_cast<int>(PlayerButton::Right), true); // Player 1 Right
                        if (autoClick_D_swiftClick && m_fields->d_clicking) {
                            this->handleButton(false, static_cast<int>(PlayerButton::Right), true);
                        }
                    }
                    m_fields->d_timer = 0;
                    if (autoClick_D_limitFrames) {
                        m_fields->d_framesClicked++;
                    }
                }
            }
        }
        
        // UP Key autoclicker
        if (autoClick_UP_enabled) {
            if (autoClick_UP_limitFrames && m_fields->up_framesClicked >= autoClick_UP_maxFrames && autoClick_UP_maxFrames > 0) {
                // Do nothing
            } else {
                m_fields->up_timer++;
                bool shouldToggle = false;
                if (!m_fields->up_clicking && m_fields->up_timer >= autoClick_UP_intervalHold) {
                    shouldToggle = true;
                } else if (m_fields->up_clicking && m_fields->up_timer >= autoClick_UP_intervalRelease) {
                    shouldToggle = true;
                }
                if (shouldToggle) {
                    m_fields->up_clicking = !m_fields->up_clicking;
                    for (int i = 0; i < autoClick_UP_clicksPerFrame; i++) {
                        this->handleButton(m_fields->up_clicking, static_cast<int>(PlayerButton::Jump), false);
                        if (autoClick_UP_swiftClick && m_fields->up_clicking) {
                            this->handleButton(false, static_cast<int>(PlayerButton::Jump), false);
                        }
                    }
                    m_fields->up_timer = 0;
                    if (autoClick_UP_limitFrames) {
                        m_fields->up_framesClicked++;
                    }
                }
            }
        }
        
        // LEFT Key autoclicker
        if (autoClick_LEFT_enabled) {
            if (autoClick_LEFT_limitFrames && m_fields->left_framesClicked >= autoClick_LEFT_maxFrames && autoClick_LEFT_maxFrames > 0) {
                // Do nothing
            } else {
                m_fields->left_timer++;
                bool shouldToggle = false;
                if (!m_fields->left_clicking && m_fields->left_timer >= autoClick_LEFT_intervalHold) {
                    shouldToggle = true;
                } else if (m_fields->left_clicking && m_fields->left_timer >= autoClick_LEFT_intervalRelease) {
                    shouldToggle = true;
                }
                if (shouldToggle) {
                    m_fields->left_clicking = !m_fields->left_clicking;
                    for (int i = 0; i < autoClick_LEFT_clicksPerFrame; i++) {
                        this->handleButton(m_fields->left_clicking, static_cast<int>(PlayerButton::Left), false);
                        if (autoClick_LEFT_swiftClick && m_fields->left_clicking) {
                            this->handleButton(false, static_cast<int>(PlayerButton::Left), false);
                        }
                    }
                    m_fields->left_timer = 0;
                    if (autoClick_LEFT_limitFrames) {
                        m_fields->left_framesClicked++;
                    }
                }
            }
        }
        
        // RIGHT Key autoclicker
        if (autoClick_RIGHT_enabled) {
            if (autoClick_RIGHT_limitFrames && m_fields->right_framesClicked >= autoClick_RIGHT_maxFrames && autoClick_RIGHT_maxFrames > 0) {
                // Do nothing
            } else {
                m_fields->right_timer++;
                bool shouldToggle = false;
                if (!m_fields->right_clicking && m_fields->right_timer >= autoClick_RIGHT_intervalHold) {
                    shouldToggle = true;
                } else if (m_fields->right_clicking && m_fields->right_timer >= autoClick_RIGHT_intervalRelease) {
                    shouldToggle = true;
                }
                if (shouldToggle) {
                    m_fields->right_clicking = !m_fields->right_clicking;
                    for (int i = 0; i < autoClick_RIGHT_clicksPerFrame; i++) {
                        this->handleButton(m_fields->right_clicking, static_cast<int>(PlayerButton::Right), false);
                        if (autoClick_RIGHT_swiftClick && m_fields->right_clicking) {
                            this->handleButton(false, static_cast<int>(PlayerButton::Right), false);
                        }
                    }
                    m_fields->right_timer = 0;
                    if (autoClick_RIGHT_limitFrames) {
                        m_fields->right_framesClicked++;
                    }
                }
            }
        }
        
        // SPACE Key autoclicker
        if (autoClick_SPACE_enabled) {
            if (autoClick_SPACE_limitFrames && m_fields->space_framesClicked >= autoClick_SPACE_maxFrames && autoClick_SPACE_maxFrames > 0) {
                // Do nothing
            } else {
                m_fields->space_timer++;
                bool shouldToggle = false;
                if (!m_fields->space_clicking && m_fields->space_timer >= autoClick_SPACE_intervalHold) {
                    shouldToggle = true;
                } else if (m_fields->space_clicking && m_fields->space_timer >= autoClick_SPACE_intervalRelease) {
                    shouldToggle = true;
                }
                if (shouldToggle) {
                    m_fields->space_clicking = !m_fields->space_clicking;
                    for (int i = 0; i < autoClick_SPACE_clicksPerFrame; i++) {
                        this->handleButton(m_fields->space_clicking, static_cast<int>(PlayerButton::Jump), true);
                        if (autoClick_SPACE_swiftClick && m_fields->space_clicking) {
                            this->handleButton(false, static_cast<int>(PlayerButton::Jump), true);
                        }
                    }
                    m_fields->space_timer = 0;
                    if (autoClick_SPACE_limitFrames) {
                        m_fields->space_framesClicked++;
                    }
                }
            }
        }
    }
};