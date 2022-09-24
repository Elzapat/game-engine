#include "../../include/vulkan_renderer/ui.hpp"

ImGui_ImplVulkanH_Window* Ui::get_window_data() {
    return &this->main_window_data;
}

void Ui::draw() {
    static bool show_demo_window = true;
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow(&show_demo_window);
    ImGui::EndFrame();
}

void Ui::render(VkCommandBuffer& command_buffer) {
    ImGui::Render();
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), command_buffer);
}
