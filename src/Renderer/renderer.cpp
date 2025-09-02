/*
#include "renderer.hpp"
#include "../paths.h"
#include "../vars.h"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

void Astral::Renderer::InstallFFmpeg() {
    std::filesystem::path FFmpegPath = AstralPath() / "ffmpeg" / "ffmpeg.exe";
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

void Astral::Renderer::Rendering() {
// add functionality later
}

void Astral::Renderer::SaveRender() {
    std::ofstream file(RendersDir() / "hi.mp4");
    if (!file.is_open()) {
        log::error("Failed to write render file");
        return;
    }
}
*/