#include "paths.h"
#include <Geode/loader/Dirs.hpp>

std::filesystem::path CorePath() {
    return geode::dirs::getGameDir() / ".core";
}

std::filesystem::path FFmpegDir() {
    return CorePath() / "ffmpeg";
}