#include "components.hpp"
#include <imgui-cocos.hpp>

bool Astral::Components::Checkbox(const char* label, bool* v, const char* description) {
	bool checkbox = false;
    
    char buf[128];
    snprintf(buf, sizeof(buf), "%s", label);

    checkbox = ImGui::Checkbox(buf, v);
	
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
        ImGui::SetTooltip("%s", description);
    }

    return checkbox;
}