#include "components.hpp"

bool Echo2::Components::Button(const char* label) {
    bool button = false;

	button = ImGui::Button(label, ImVec2(-1, 0));

    return button;
}

bool Echo2::Components::ButtonSquare(const char* label) {
    bool buttonSmall = false;

	buttonSmall = ImGui::Button(label, ImVec2(60, 60));

    return buttonSmall;
}