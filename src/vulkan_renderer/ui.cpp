#include "../../include/vulkan_renderer/ui.hpp"

ImGui_ImplVulkanH_Window* Ui::get_window_data() {
    return &this->main_window_data;
}

void Ui::draw(Camera& camera) {
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(25, 25), ImGuiCond_FirstUseEver);

    static bool window_opened = true;
    ImGui::Begin("Inspector", &window_opened, ImGuiWindowFlags_NoMove);

    // Average frame tima and fps over one second
    {
        static float average_counter = 0.0f;
        static float average_frame_time = 0.0f;
        static int average_fps = 0.0f;
        static int frames_count = 0;

        frames_count++;
        average_counter += Time::delta_time();

        if (average_counter >= 1.0f) {
            average_frame_time = average_counter / frames_count;
            average_fps = frames_count;

            average_counter = 0.0f;
            frames_count = 0;
        }

        ImGui::Text("Frame time: %f, FPS: %d", average_frame_time, average_fps);
    }

    ImGui::Text(
        "Press Y to enable or disable the mouse\nMouse enabled = %s",
        camera.mouse_disabled ? "true" : "false"
    );

    if (ImGui::CollapsingHeader("Camera")) {
        ImGui::SliderFloat("Movement speed", &camera.speed, 0.0f, 10.0f);
        ImGui::SliderFloat("Mouse sensitivity", &camera.sensitivity, 0.01f, 0.2f);
    }

    /* ImGui::Text("%d particules", n_particules); */
    /*  */
    /* if (ImGui::Button("Spawn new particule")) {} */

    ImGui::End();

    ImGui::EndFrame();
}

void Ui::render(VkCommandBuffer& command_buffer) {
    ImGui::Render();
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), command_buffer);
}
