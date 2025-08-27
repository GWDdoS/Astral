#include "components.hpp"
#include <imgui-cocos.hpp>

void Astral::Components::Text(const char* text) {
    ImGui::Text("%s", text);
}