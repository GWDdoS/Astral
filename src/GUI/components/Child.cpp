#include "components.hpp"
#include <imgui-cocos.hpp>

bool Astral::Components::BeginChild(const char* text, int width, int height, bool* open) {
    bool beginChild = false;

    beginChild = ImGui::BeginChild(text, ImVec2(width, height), true);

    return beginChild;
}

void Astral::Components::EndChild() {
    ImGui::EndChild();
}