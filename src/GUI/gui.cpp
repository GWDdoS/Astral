#include "gui.hpp"
#include "button.cpp" // Does this mean i can do button?


// This is an example for ImGUI? idk if ti works tho
void ShowSimpleBox() {
    ImGui::Begin("Box Window"); 

    ImVec2 boxSize(200, 100); // Width, Height
    ImVec2 cursorPos = ImGui::GetCursorScreenPos();

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRect(
        cursorPos, 
        ImVec2(cursorPos.x + boxSize.x, cursorPos.y + boxSize.y),
        IM_COL32(255, 255, 255, 255), // White box
        0.0f,                         // Corner rounding
        0,                            // Corner flags
        2.0f                          // Thickness
    );
    ImGui::End(); // End window
}