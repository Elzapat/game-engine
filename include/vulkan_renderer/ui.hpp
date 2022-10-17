#ifndef UI_HPP
#define UI_HPP

#include "../../libs/imgui/backends/imgui_impl_vulkan.h"
#include "../../libs/imgui/backends/imgui_impl_glfw.h"
#include "../../libs/glfw/include/GLFW/glfw3.h"

#include "../math/vector3D.hpp"
#include "../physics_engine/physic_world.hpp"
#include "../physics_engine/particle.hpp"
#include "camera.hpp"

#include <vulkan/vulkan.h>
#include <memory>

class Ui {
    public:
        void draw(Camera& camera);
        void render(VkCommandBuffer& command_buffer);
        ImGui_ImplVulkanH_Window* get_window_data();

    private:
        ImGui_ImplVulkanH_Window main_window_data;
};

#endif // UI_HPP
