#include "bot.hpp"
#include <Geode/modify/GJBaseGameLayer.hpp>

class $modify(GJBaseGameLayer) {
    void handleButton(bool down, int button, bool isPlayer1) {
        GJBaseGameLayer::handleButton(down, button, isPlayer1);
    }
};

void Core::Bot::Save() {

}