#include "components.hpp"

void Core::Components::Text(const char* text) {
    char buf[128];
    snprintf(buf, sizeof(buf), "%s", text);

    ImGui::Text(buf);
}