#include "../../include/vulkan_renderer/ui.hpp"

ImGui_ImplVulkanH_Window* Ui::get_window_data() {
    return &this->main_window_data;
}

void Ui::draw(int n_particules, Particule& particule) {
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowSize(ImVec2(200, 400), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(25, 25), ImGuiCond_FirstUseEver);

    static bool window_opened = true;
    ImGui::Begin("Particule inspector", &window_opened, ImGuiWindowFlags_NoMove);

    const float bounds = 10.0f;

    float damping = particule.get_damping();
    ImGui::SliderFloat("damping", &damping, 0.0f, 1.0f);
    particule.set_damping(damping);

    if (ImGui::CollapsingHeader("Position")) {
        math::Vector3D pos = particule.get_position();
        float pos_x = pos.get_x(), pos_y = pos.get_y(), pos_z = pos.get_z();

        ImGui::SliderFloat("pos_x", &pos_x, -bounds, bounds);
        ImGui::SliderFloat("pos_y", &pos_y, -bounds, bounds);
        ImGui::SliderFloat("pos_z", &pos_z, -bounds, bounds);

        particule.set_position(math::Vector3D(pos_x, pos_y, pos_z));
    }

    if (ImGui::CollapsingHeader("Velocity")) {
        math::Vector3D vel = particule.get_velocity();
        float vel_x = vel.get_x(), vel_y = vel.get_y(), vel_z = vel.get_z();

        ImGui::SliderFloat("vel_x", &vel_x, -bounds, bounds);
        ImGui::SliderFloat("vel_y", &vel_y, -bounds, bounds);
        ImGui::SliderFloat("vel_z", &vel_z, -bounds, bounds);

        particule.set_velocity(math::Vector3D(vel_x, vel_y, vel_z));
    }

    if (ImGui::CollapsingHeader("Acceleration")) {
        math::Vector3D accel = particule.get_acceleration();
        float accel_x = accel.get_x(), accel_y = accel.get_y(), accel_z = accel.get_z();

        ImGui::SliderFloat("accel_x", &accel_x, -bounds, bounds);
        ImGui::SliderFloat("accel_y", &accel_y, -bounds, bounds);
        ImGui::SliderFloat("accel_z", &accel_z, -bounds, bounds);

        particule.set_acceleration(math::Vector3D(accel_x, accel_y, accel_z));
    }

    ImGui::Text("%d particules", n_particules);

    if (ImGui::Button("Spawn new particule")) {}

    ImGui::End();

    ImGui::EndFrame();
}

void Ui::render(VkCommandBuffer& command_buffer) {
    ImGui::Render();
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), command_buffer);
}
