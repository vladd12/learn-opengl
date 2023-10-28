project(glad LANGUAGES C)

# Setting up some useful directory variables
set(GLAD_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(GLAD_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Collecting GLAD library sources
set(GLAD_SOURCES
    "${GLAD_HEADERS}/glad/glad.h"
    "${GLAD_HEADERS}/KHR/khrplatform.h"
    "${GLAD_SOURCES}/glad.c"
)

# Adding GLAD library target and its alias
add_library(glad STATIC ${GLAD_SOURCES})
add_library(glad::glad ALIAS glad)

# Setting up include directory for main project
target_include_directories(glad PUBLIC $<BUILD_INTERFACE:${GLAD_HEADERS}>)

