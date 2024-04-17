#include "gl3d/global_init.h"

#include <GLFW/glfw3.h>

namespace GL3D
{

GlobalInit::GlobalInit(token) noexcept : initStatus(glfwInit())
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GlobalInit::~GlobalInit() noexcept
{
    glfwTerminate();
}

void GlobalInit::reinit() noexcept
{
    glfwTerminate();
    initStatus = glfwInit();
}

GlobalInit::operator bool() const noexcept
{
    return initStatus;
}

} // namespace GL3D
