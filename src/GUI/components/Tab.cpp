#include "components.hpp"
#include <imgui.h>
#include <imgui_internal.h>

void Astral::Components::Begin(int xpos, int ypos, int width, int height, const char* text, bool* open) {
    ImGui::SetNextWindowPos(ImVec2(xpos, ypos));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    /*
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove;
    ImGui::Begin(text, open, flags);*/
}

void Astral::Components::End() {
    ImGui::End();
}