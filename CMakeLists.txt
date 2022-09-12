cmake_minimum_required(VERSION 3.1.0)

project(mathematiques-et-physique-pour-le-jeu-video-projet-de-session)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mathematiques-et-physique-pour-le-jeu-video-projet-de-session
  src/main.cpp

  src/vector3D.cpp
  include/vector3D.hpp

  src/particule.cpp
  include/particule.hpp
)

target_link_libraries(mathematiques-et-physique-pour-le-jeu-video-projet-de-session m)
