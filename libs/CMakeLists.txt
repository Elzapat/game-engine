# GLFW
add_subdirectory(glfw)

# ImGUI
file(GLOB IMGUI_SOURCES imgui/*.cpp imgui/backends/imgui_impl_vulkan.cpp imgui/backends/imgui_impl_glfw.cpp)
add_library("imgui" ${IMGUI_SOURCES})
target_include_directories("imgui" PUBLIC 
    imgui
    imgui/backends
    ../libs/glfw/include
    ../libs/glm
)
if(WIN32)
    target_include_directories("imgui" PUBLIC     C:/VulkanSDK/1.3.224.1/Include)
endif()
link_libraries(vulkan)

# GLM
add_subdirectory(glm)