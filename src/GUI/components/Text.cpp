#include "components.hpp"

void Echo2::Components::Text(const char* text) {
    char buf[128];
    snprintf(buf, sizeof(buf), "%s", text);

    ImGui::Text(buf);
}