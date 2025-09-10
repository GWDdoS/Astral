#include "mobileUI.hpp"

#ifdef GEODE_IS_MOBILE
Ref<Astral_GUI_Mobile_UI> ins;
#define HorizontalInset 8
#define VerticalInset 9

bool Astral_GUI_Mobile_UI::setup() {
    this->setAnchorPoint({0.5, 0});
    this->runAction(CCFadeTo::create(0.5f, 100));
    this->setKeypadEnabled(true);
    this->setTitle("Astral Bot:", "bigFont.fnt", 0.7f, -12.5f);
    
    m_mainLayer->setLayoutOptions(AnchorLayoutOptions::create()->setAnchor(Anchor::Center));
    m_mainLayer->updateLayout();
    
    auto bgRight = CCScale9Sprite::create("square02_001.png");
    bgRight->setAnchorPoint(ccp(1, 0.5f));
    bgRight->setOpacity(60);
    bgRight->setContentWidth((this->m_size.width / 2) - HorizontalInset * 2);
    bgRight->setContentHeight(this->m_size.height - VerticalInset * 2.5);
    bgRight->setScale(1.0f / 2.0f);
    bgRight->setContentSize(bgRight->getContentSize() * 2);
    
    auto rightMenu = CCMenu::create();
    rightMenu->setLayout(AxisLayout::create()->setAxis(Axis::Column));
    rightMenu->setAnchorPoint(ccp(1, -0.5f));
    
    auto bgLeft = CCScale9Sprite::create("square02_001.png");
    bgLeft->setAnchorPoint(ccp(1, 0.5f));
    bgLeft->setOpacity(40);
    bgLeft->setContentWidth((this->m_size.width / 3.2) - HorizontalInset * 2);
    bgLeft->setContentHeight(this->m_size.height - VerticalInset * 2.5);
    bgLeft->setScale(1.0f / 2.0f);
    bgLeft->setContentSize(bgLeft->getContentSize() * 2);
    
    leftMenu = CCMenu::create();
    leftMenu->setLayout(AxisLayout::create()->setAxis(Axis::Column));
    leftMenu->setAnchorPoint(ccp(0.f, 0.5f));
    
    // tabs
    createTabBtn("Bot", menu_selector(Astral_GUI_Mobile_UI::onSettings));
    
    m_mainLayer->addChildAtPosition(bgRight, Anchor::Right, ccp(-HorizontalInset, 0));
    m_mainLayer->addChildAtPosition(rightMenu, Anchor::Right, ccp(-10, 0));
    m_mainLayer->addChildAtPosition(bgLeft, Anchor::Left, ccp(HorizontalInset + 101, 0));
    m_mainLayer->addChildAtPosition(leftMenu, Anchor::Left, ccp(17.5, 0));
    
    return true;
}

void Astral_GUI_Mobile_UI::createTabBtn(const char* text, SEL_MenuHandler callback) {
    auto spr = ButtonSprite::create(text, 65, 69420, .75f, true, "bigFont.fnt", "GJ_button_04.png", 30);
    
    auto btn = CCMenuItemSpriteExtra::create(spr, this, callback);
    
    leftMenu->addChild(btn);
    leftMenu->updateLayout();
}

void Astral_GUI_Mobile_UI::onClose(CCObject* sender) {
    this->removeFromParent();
}

void Astral_GUI_Mobile_UI::keyBackClicked() {
    onClose(nullptr);
}

void Astral_GUI_Mobile_UI::onSettings(CCObject*) {
    geode::openSettingsPopup(Mod::get());
}

Astral_GUI_Mobile_UI* Astral_GUI_Mobile_UI::create() {
    auto pRet = new Astral_GUI_Mobile_UI();
    
    if (pRet && pRet->initAnchored(380, 240, "GJ_square05.png"))
    {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return nullptr;
}
#endif