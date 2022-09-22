#ifndef UI_HPP
#define UI_HPP

#include "../../libs/imgui/backends/imgui_impl_vulkan.h"
#include "../../libs/glfw/include/GLFW/glfw3.h"

#include <vulkan/vulkan.h>

class Ui {
    public:
        void update();
        ImGui_ImplVulkanH_Window* get_window_data();

    private:
        ImGui_ImplVulkanH_Window main_window_data;
};

#endif // UI_HPP
