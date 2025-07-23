#include "mobileUI.hpp"

Ref<Core_GUI_Mobile_UI> ins;
#define HorizontalInset 8
#define VerticalInset 9

bool Core_GUI_Mobile_UI::setup() {
    this->setAnchorPoint({0.5, 0});
    this->runAction(CCFadeTo::create(0.5f, 100));
    this->setKeypadEnabled(true);
    this->setTitle("CORE Bot:", "bigFont.fnt", 0.7f, -12.5f);

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

    m_obNext = ccp(0.f, 75.f);

    // bottom to top
    createTabBtn("Render", menu_selector(Core_GUI_Mobile_UI::onSettings));
    createTabBtn("Bot", menu_selector(Core_GUI_Mobile_UI::onSettings));

    m_mainLayer->addChildAtPosition(bgRight, Anchor::Right, ccp(-HorizontalInset, 0));
    m_mainLayer->addChildAtPosition(rightMenu, Anchor::Right, ccp(-10, 0));
    m_mainLayer->addChildAtPosition(bgLeft, Anchor::Left, ccp(HorizontalInset + 101, 0));
    m_mainLayer->addChildAtPosition(leftMenu, Anchor::Left, ccp(17.5, 0));

    return true;
}

void Core_GUI_Mobile_UI::createTabBtn(const char* text, SEL_MenuHandler callback) {
    auto spr = ButtonSprite::create(text, 65, 69420, .75f, true, "bigFont.fnt", "GJ_button_04.png", 30);

    auto btn = CCMenuItemSpriteExtra::create(spr, this, callback);
    btn->setPosition(m_obNext.x - 120.f, m_obNext.y + 10.f);
    
    leftMenu->addChild(btn);
    leftMenu->updateLayout();

    m_obNext.y = m_obNext.y - 45.f;
}

void Core_GUI_Mobile_UI::onClose(CCObject* sender) {
    this->removeFromParent();
}

void Core_GUI_Mobile_UI::keyBackClicked() {
    onClose(nullptr);
}

void Core_GUI_Mobile_UI::onSettings(CCObject*) {
    geode::openSettingsPopup(Mod::get());
}

Core_GUI_Mobile_UI* Core_GUI_Mobile_UI::create() {
    auto pRet = new Core_GUI_Mobile_UI();

    if (pRet && pRet->initAnchored(380, 240, "GJ_square05.png")) {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}