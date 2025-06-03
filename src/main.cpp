#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

bool init() {
    if (!MenuLayer::init())
    return false;

    auto alert = FLAlertLayer::create(
        "Hello",
        "The mod built, Now we can rethink our life choices!",
        "YAY"
    );
       alert->m_scene = this;
       alert->show();

       return true;
    }
};
