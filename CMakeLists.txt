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
