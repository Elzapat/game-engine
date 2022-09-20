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

add_subdirectory(include/glfw)

find_package(Vulkan REQUIRED)

add_executable(physics-engine
  src/main.cpp

  src/vector3D.cpp
  include/vector3D.hpp

  src/particule.cpp
  include/particule.hpp

  src/vulkan_renderer.cpp
  include/vulkan_renderer.hpp
)

target_include_directories(physics-engine
  PUBLIC ${VULKAN_INCLUDE_DIRS}
)

target_link_libraries(physics-engine
  m
  glfw
  ${VULKAN_LIB_LIST}
)
