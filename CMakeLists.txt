# Project definition and settings
cmake_minimum_required(VERSION 3.15)
project(learn-opengl VERSION 0.1 LANGUAGES C CXX)

# Language settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding path for cmake scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(get_gtest) # Getting googletest library
include(get_glfw)  # Getting GLFW library

add_subdirectory(glad) # Getting GLAD library

set(GL3D_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/gl3d")
set(GL3D_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/gl3d")

set(GL3D_PUBLIC_HEADERS "${GL3D_INCLUDE_DIR}/window.h")
set(GL3D_PRIVATE_HEADERS
  "${GL3D_SRC_DIR}/private/singleton.h"
  "${GL3D_SRC_DIR}/private/global_init.h"
)
set(GL3D_SOURCES
  "${GL3D_SRC_DIR}/private/global_init.cpp"
  "${GL3D_SRC_DIR}/window.cpp"
)

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  FILES ${GL3D_PUBLIC_HEADERS} ${GL3D_PRIVATE_HEADERS} ${GL3D_SOURCES}
)

add_library(gl3d STATIC
  ${GL3D_PUBLIC_HEADERS}
  ${GL3D_PRIVATE_HEADERS}
  ${GL3D_SOURCES}
)

target_include_directories(gl3d PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_include_directories(gl3d PRIVATE
  "$<BUILD_INTERFACE:${GL3D_SRC_DIR}>")

target_link_libraries(gl3d PRIVATE glad::glad glfw::glfw)

# Collecting project's sources
set(LEARN_OPENGL_SOURCES
    src/main.cpp
    src/shaders/triangle_shaders.hpp
)

# Creating executable target
add_executable(${PROJECT_NAME} ${LEARN_OPENGL_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Linking GLAD and GLFW libraries
target_link_libraries(${PROJECT_NAME} PUBLIC glad::glad glfw::glfw)
