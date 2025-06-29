#include "components.hpp"

void Core::Components::Begin(int xpos, int ypos, int width, int height, const char* text, bool* open) {
    ImGui::SetNextWindowPos(ImVec2(xpos, ypos));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin(text, open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
}

void Core::Components::End() {
    ImGui::End();
}