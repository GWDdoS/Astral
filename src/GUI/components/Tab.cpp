#include "components.hpp"
#include <Imgui-cocos.hpp>

void Astral::Components::Begin(int xpos, int ypos, int width, int height, const char* text, bool* open) {
    ImGui::SetNextWindowPos(ImVec2(xpos, ypos));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar;
    ImGui::Begin(text, open, flags);
    // https://github.com/GMDPLUTONIC/gd-imgui-cocos
}

void Astral::Components::End() {
    ImGui::End();
}