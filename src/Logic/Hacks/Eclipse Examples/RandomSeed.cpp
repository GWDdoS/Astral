/*
#include <modules/config/config.hpp>
#include <modules/gui/gui.hpp>
#include <modules/gui/components/toggle.hpp>
#include <modules/hack/hack.hpp>

#include <Geode/modify/GameToolbox.hpp>

#ifndef GEODE_IS_WINDOWS // TODO: Make a patch for Windows
namespace eclipse::hacks::Level {
    class $hack(RandomSeed) {
        void init() override {
            auto tab = gui::MenuTab::find("tab.level");

            config::setIfEmpty("level.randomseed.seed", 1);

            tab->addToggle("level.randomseed")
               ->handleKeybinds()
               ->setDescription()
               ->addOptions([](std::shared_ptr<gui::MenuTab> options) {
                   options->addInputInt("level.randomseed.seed", "level.randomseed.seed");
               });
        }

        [[nodiscard]] bool isCheating() const override { return config::get<"level.randomseed", bool>(); }
        [[nodiscard]] const char* getId() const override { return "Random Seed"; }
    };

    REGISTER_HACK(RandomSeed)

    class $modify(GameToolbox) {
        ALL_DELEGATES_AND_SAFE_PRIO("level.randomseed")

        float fast_rand_0_1() {
            int newSeed = (214'013 * config::get<int>("level.randomseed.seed", false)) + 2'531'011;

            return ((newSeed >> 16) & 0x7FFF) / 32767.f;
        }
    };
}

#endif
*/