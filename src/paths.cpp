#include "paths.h"
#include <Geode/loader/Dirs.hpp>

std::filesystem::path AstralPath() {
    return geode::dirs::getGameDir() / "astral";
}

std::filesystem::path FFmpegDir() {
    return AstralPath() / "ffmpeg";
}

std::filesystem::path RendersDir() {
    return AstralPath() / "renders";
}

std::filesystem::path MacrosDir() {
    return AstralPath() / "macros";
}
std::filesystem::path CustomDir() {
    return AstralPath() / "customtest";
}
std::filesystem::path LogsDir() {
    return AstralPath() / "logs";
}
std::ofstream file(MacrosDir() / "test.ast");