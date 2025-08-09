#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "../gui.hpp"

using namespace geode::prelude;

class Core_GUI_Mobile_UI : public Popup<> {
    public:
        virtual bool setup();

        CCMenu* leftMenu;
        CCMenu* rightMenu;

        CCPoint m_obNext;

        void onClose(CCObject* sender);
        void keyBackClicked();

        void createTabBtn(const char* text, SEL_MenuHandler callback);

        void onSettings(CCObject*);
        void onSave(CCObject* sender);

        static Core_GUI_Mobile_UI* create();
};

class SavePopup : public Popup<> {
    public:
        virtual bool setup();
        
        void onClose(CCObject* sender);
        void keyBackClicked();

        static SavePopup* create();
};