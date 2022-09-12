cmake_minimum_required(VERSION 3.1.0)

project(physics-engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(physics-engine
  src/main.cpp

  src/vector3D.cpp
  include/vector3D.hpp

  src/particule.cpp
  include/particule.hpp
)

target_link_libraries(physics-engine m)
