#include "components.hpp"

bool Echo2::Components::BeginChild(const char* text, int width, int height, bool* open) {
    bool beginChild = false;

    beginChild = ImGui::BeginChild(text, ImVec2(width, height), true);

    return beginChild;
}

void Echo2::Components::EndChild() {
    ImGui::EndChild();
}