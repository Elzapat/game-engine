# GLFW
add_subdirectory(glfw)

# ImGUI
include_directories(imgui imgui/backends)
file(GLOB IMGUI_SOURCES imgui/*.cpp imgui/backends/imgui_impl_vulkan.cpp imgui/backends/imgui_impl_glfw.cpp)
add_library("imgui" ${IMGUI_SOURCES})
target_include_directories("imgui" PUBLIC imgui)
