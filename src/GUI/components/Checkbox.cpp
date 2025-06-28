#include "components.hpp"

bool Echo2::Components::Checkbox(const char* label, bool* v, const char* description) {
	bool checkbox = false;

	checkbox = ImGui::Checkbox(label, v);
	
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
        ImGui::SetTooltip("%s", description);
    }

    return checkbox;
}