#include "renderer.hpp"
#include "../paths.h"
#include "../vars.h"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/modify/CCScheduler.hpp>

using namespace geode::prelude;

void Core::Renderer::InstallFFmpeg() {
    std::filesystem::path FFmpegPath = CorePath() / "ffmpeg" / "ffmpeg.exe";
    web::WebRequest()
        .get("https://github.com/GMDPLUTONIC/test/releases/download/hii/ffmpeg.exe")
        .listen([FFmpegPath](auto res) {
            if (!res) return;
            auto intoRes = res->into(FFmpegPath);
            if (!intoRes) {
                Notification::create("FFmpeg has failed to download", NotificationIcon::Error, 1.f);
            } else {
                Notification::create("FFmpeg has been successfully downloaded", NotificationIcon::Success, 1.f);
            }
        });
}

void Core::Renderer::Rendering() {
// add functionality later
}

void Core::Renderer::SaveRender() {
    std::ofstream file(RendersDir() / "hi.mp4");
    if (!file.is_open()) {
        log::error("Failed to write render file");
        return;
    }
}