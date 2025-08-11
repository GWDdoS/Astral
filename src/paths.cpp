#include "paths.h"
#include <Geode/loader/Dirs.hpp>

std::filesystem::path AstralPath() {
    return geode::dirs::getGameDir() / ".astral";
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