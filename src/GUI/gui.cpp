#include <imgui-cocos.hpp>

$on_mod(Loaded) {
    ImGuiCocos::get().setup([] {
        // this runs after imgui has been setup,
        // its a callback as imgui will be re initialized when toggling fullscreen,
        // so use this to setup any themes and or fonts!
    }).draw([] {
        ImGui::Begin("My awesome window");

        ImGui::Button("Awesome button");
        
        ImGui::End();
    });
}