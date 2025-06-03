#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(EchoTest, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto bottomMenu = this->getChildByID("bottom-menu");
        if (bottomMenu) {
            auto newgroundsButton = bottomMenu->getChildByID("newgrounds-button");
            if (newgroundsButton) {
                newgroundsButton->setScale(1.5f);
            }
        }
        return true;
    }
};
