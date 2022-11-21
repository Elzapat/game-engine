#include "vulkan_renderer/ui.hpp"

math::Vector3 Ui::spring_anchor = math::Vector3();
float Ui::anchored_spring_rest_length = 1.0f;

ImGui_ImplVulkanH_Window* Ui::get_window_data() {
    return &this->main_window_data;
}

void Ui::draw(Camera& camera, std::vector<std::shared_ptr<Particle>>& particles) {
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

    ImGui::Text("Use WASD, A, E and the mouse to control the camera");
    ImGui::Text(
        "Press Y to enable or disable the mouse\nMouse enabled = %s",
        camera.mouse_disabled ? "true" : "false"
    );

    if (ImGui::CollapsingHeader("Camera")) {
        ImGui::SliderFloat("Movement speed", &camera.speed, 0.0f, 30.0f);
        ImGui::SliderFloat("Mouse sensitivity", &camera.sensitivity, 0.01f, 0.2f);
    }

    if (ImGui::CollapsingHeader("Spring anchor")) {
        float x = Ui::spring_anchor.get_x(), y = Ui::spring_anchor.get_y(),
              z = Ui::spring_anchor.get_z();
        ImGui::SliderFloat("x", &x, -100.0f, 100.0f);
        ImGui::SliderFloat("y", &y, -100.0f, 100.0f);
        ImGui::SliderFloat("z", &z, -100.0f, 100.0f);

        ImGui::SliderFloat("rest_length", &Ui::anchored_spring_rest_length, 0.0f, 50.0f);

        Ui::spring_anchor = math::Vector3(x, y, z);
    }

    ImGui::End();
    ImGui::EndFrame();
}

void Ui::render(VkCommandBuffer& command_buffer) {
    ImGui::Render();
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), command_buffer);
}
