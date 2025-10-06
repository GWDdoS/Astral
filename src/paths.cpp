#include "paths.h"
#include <Geode/loader/Dirs.hpp>

std::filesystem::path AstralPath() {
    return geode::dirs::getGameDir() / "Astral";
}

std::filesystem::path FFmpegDir() {
    return AstralPath() / "ffmpeg";
}

std::filesystem::path RendersDir() {
    return AstralPath() / "Renders";
}

std::filesystem::path MacrosDir() {
    return AstralPath() / "Macros";
}
std::filesystem::path CustomDir() {
    return AstralPath() / "CustomeTest";
}