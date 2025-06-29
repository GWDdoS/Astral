#include "renderer.hpp"
#include "../paths.h"
#include "../vars.h"
#include <Geode/loader/Dirs.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <Geode/loader/Mod.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/modify/CCScheduler.hpp>

using namespace geode::prelude;

void Core::Renderer::InstallFFmpeg() {
    std::filesystem::path corePath = geode::dirs::getGameDir() / ".core";
    std::filesystem::path FFmpegPath = corePath / "ffmpeg" / "ffmpeg.exe";

    web::WebRequest()
        .get("https://github.com/GMDPLUTONIC/test/releases/download/hii/ffmpeg.exe")
        .listen([FFmpegPath](auto res) {
            if (!res) return;
            auto intoRes = res->into(FFmpegPath);
            if (!intoRes) {
                Notification::create("Failed downloading FFmpeg", geode::NotificationIcon::Error, 1.f);
            } else {
                Notification::create("Succes downloading FFmpeg", geode::NotificationIcon::Success, 1.f);
            }
        });
}

void Core::Renderer::Rendering() {
// add functionality later
}

void Core::Renderer::SaveRender() {
// add functionality later
}