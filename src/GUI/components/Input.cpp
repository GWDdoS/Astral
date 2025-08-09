#include "components.hpp"

bool Astral::Components::InputFloat(const char* label, float* v, float step, float step_fast, const char* format) {
    bool inputFloat = false;

    ImGui::InputFloat(label, v, step, step_fast, format);

    return inputFloat;
}

bool Astral::Components::InputInt(const char* label, int* v) {
    bool inputInt = false;

    inputInt = ImGui::InputInt(label, v);

    return inputInt;
}