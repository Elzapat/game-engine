#ifndef UI_HPP
#define UI_HPP

#include "../../libs/imgui/backends/imgui_impl_vulkan.h"
#include "../../libs/imgui/backends/imgui_impl_glfw.h"
#include "../../libs/glfw/include/GLFW/glfw3.h"

#include "../math/vector3.hpp"
#include "../physics_engine/particle.hpp"
#include "camera.hpp"

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>

class Ui {
    public:
        void draw(Camera& camera);
        void render(VkCommandBuffer& command_buffer);
        ImGui_ImplVulkanH_Window* get_window_data();
        static math::Vector3 spring_anchor;
        static float anchored_spring_rest_length;

    private:
        ImGui_ImplVulkanH_Window main_window_data;
};

#endif // UI_HPP
