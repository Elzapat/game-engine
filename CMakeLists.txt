cmake_minimum_required(VERSION 3.1.0)

project(physics-engine)

# C++20 required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug build
set(CMAKE_BUILD_TYPE Debug)

# Disable building of docs, tests and examples of GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Put the compiled binaries in their respective directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_subdirectory(libs)

find_package(Vulkan REQUIRED)

add_executable(physics-engine
    src/main.cpp

    src/math/vector3D.cpp
    include/math/vector3D.hpp

    src/physics_engine/particule.cpp
    include/physics_engine/particule.hpp

    src/vulkan_renderer/vulkan_renderer_init.cpp
    src/vulkan_renderer/vulkan_renderer_cleanup.cpp
    src/vulkan_renderer/vulkan_renderer_update.cpp
    src/vulkan_renderer/vulkan_renderer_debug.cpp
    include/vulkan_renderer/vulkan_renderer.hpp
    
    src/vulkan_renderer/ui.cpp
    include/vulkan_renderer/ui.hpp

    src/vulkan_renderer/renderer_utils.cpp
    include/vulkan_renderer/renderer_utils.hpp
)

# GLSL Shader compilation to Vulkan compatabile SPV fromat
find_program(glslc_exe NAMES glslc HINTS Vulkan::glslc)

set(SHADER_SOURCE_DIR src/shaders)
set(SHADER_BINARY_DIR bin/shaders)

file(MAKE_DIRECTORY ${SHADER_BINARY_DIR})
file(GLOB SHADERS ${SHADER_SOURCE_DIR}/*.vert ${SHADER_SOURCE_DIR}/*.frag)

foreach(source IN LISTS SHADERS)
    get_filename_component(FILENAME ${source} NAME)

    add_custom_command(
        COMMAND ${glslc_exe} -o ${SHADER_BINARY_DIR}/${FILENAME}.spv ${source}
        OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
        DEPENDS ${source} ${SHADER_BINARY_DIR}
        COMMENT "Compiling shader ${FILENAME}"
    )

    list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
endforeach()

add_custom_target(shaders ALL DEPENDS ${SPV_SHADERS})

# Libraries to link against
target_include_directories(physics-engine
    PUBLIC ${VULKAN_INCLUDE_DIRS}
)

target_link_libraries(physics-engine
    m
    glfw
    imgui
    vulkan
) 
