#pragma once

#include <imgui-cocos.hpp>

namespace Astral::Components {
    // Tab
    //void Begin(int xpos, int ypos, int width, int height, const char* text, bool *open = nullptr);
void Begin(const char* text, bool *open = nullptr);
    void End();

    // Child
    bool BeginChild(const char* text, int width, int height, bool* open = nullptr);
    void EndChild();

    // Line
    void LineGap();
    void SameLine();

    // Button
    bool Button(const char* label);
    bool ButtonSquare(const char* label);

    // Input
    bool InputFloat(const char* label, float* v, float step, float step_fast, const char* format);
    bool InputInt(const char* label, int* v);

    // Checkbox
    bool Checkbox(const char* label, bool* v, const char* description);

    // Text
    void Text(const char* text);
}