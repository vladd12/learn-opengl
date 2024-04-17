# Collecting sources
set(GL3D_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# Creating executable target
add_executable(gl3d_test ${GL3D_TEST_SOURCES})

# Linking dependencies
target_link_libraries(gl3d_test PRIVATE gl3d glad::glad glfw::glfw)
