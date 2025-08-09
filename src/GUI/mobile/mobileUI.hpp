#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "../gui.hpp"

using namespace geode::prelude;

class Astral_GUI_Mobile_UI: public Popup<> {
    public:
        virtual bool setup();

        CCMenu* leftMenu;
        CCMenu* rightMenu;

        CCPoint m_obNext;

        void onClose(CCObject* sender);
        void keyBackClicked();

        void createTabBtn(const char* text, SEL_MenuHandler callback);

        void onSettings(CCObject*);

        static Astral_GUI_Mobile_UI* create();
        static Astral_GUI_Mobile_UI* get();
};