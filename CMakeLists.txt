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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(libs)

find_package(Vulkan REQUIRED)

if(WIN32)
    find_library(VULKAN NAMES Vulkan PATHS "C:/VulkanSDK/1.3.224.1")
    find_library(GLFW NAMES glfw PATHS "libs/glfw")
    find_library(GLM NAMES glm PATHS "libs/glm")
endif()

add_executable(physics-engine
    src/main.cpp

    src/game_engine.cpp
    src/app.cpp

    src/time.cpp

    src/math/vector3.cpp
    src/math/quaternion.cpp
    src/math/matrix3.cpp
    src/math/matrix4.cpp

    src/physics_engine/physic_world.cpp
    src/physics_engine/particle.cpp
    src/physics_engine/rigid_body.cpp

    src/physics_engine/forces/particles/particle_force_registry.cpp
    src/physics_engine/forces/particles/particle_force_generator.cpp
    src/physics_engine/forces/particles/particle_drag.cpp
    src/physics_engine/forces/particles/particle_spring.cpp
    src/physics_engine/forces/particles/particle_anchored_spring.cpp
    src/physics_engine/forces/particles/particle_buoyancy.cpp
    src/physics_engine/forces/particles/particle_gravity.cpp

    src/physics_engine/forces/rigid_bodies/force_generator.cpp
    src/physics_engine/forces/rigid_bodies/force_registry.cpp

    src/physics_engine/contacts/particles/particle_contact.cpp
    src/physics_engine/contacts/particles/particle_rod.cpp
    src/physics_engine/contacts/particles/particle_link.cpp
    src/physics_engine/contacts/particles/particle_cable.cpp
    src/physics_engine/contacts/particles/naive_particle_contact_generator.cpp
    src/physics_engine/contacts/particles/particle_contact_resolver.cpp

    src/vulkan_renderer/vulkan_renderer_init.cpp
    src/vulkan_renderer/vulkan_renderer_cleanup.cpp
    src/vulkan_renderer/vulkan_renderer_update.cpp
    src/vulkan_renderer/vulkan_renderer_debug.cpp
    src/vulkan_renderer/ui.cpp
    src/vulkan_renderer/renderer_utils.cpp
    src/vulkan_renderer/camera.cpp
    src/vulkan_renderer/mesh.cpp

    src/test_scenes/test_cable.cpp
)

target_include_directories(physics-engine PRIVATE include libs libs/glfw/include)

# GLSL Shader compilation to Vulkan compatabile SPV fromat
find_program(glslc_exe NAMES glslc HINTS Vulkan::glslc)

set(SHADER_SOURCE_DIR src/shaders)
set(SHADER_BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)

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
include_directories(physics-engine PUBLIC ${VULKAN_INCLUDE_DIRS})

target_link_libraries(physics-engine
    m
    glfw
    imgui
)

if(MSVC)
    target_compile_options(physics-engine PRIVATE /W4)
else()
    target_compile_options(physics-engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(WIN32)
    target_link_libraries(physics-engine Vulkan::Vulkan)
else()
    target_link_libraries(physics-engine vulkan)
endif()
