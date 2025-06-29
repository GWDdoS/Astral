#include "components.hpp"

bool Core::Components::BeginChild(const char* text, int width, int height, bool* open) {
    bool beginChild = false;

    beginChild = ImGui::BeginChild(text, ImVec2(width, height), true);

    return beginChild;
}

void Core::Components::EndChild() {
    ImGui::EndChild();
}