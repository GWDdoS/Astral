#include "components.hpp"
#include <imgui.h>
#include <imgui_internal.h>

void Core::Components::Begin(int xpos, int ypos, int width, int height, const char* text, bool* open) {
    ImGui::SetNextWindowPos(ImVec2(xpos, ypos), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove;
    ImGui::Begin(text, open, flags);
}

void Core::Components::End() {
    ImGui::End();
}