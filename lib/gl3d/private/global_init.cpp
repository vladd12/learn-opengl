#include "private/global_init.h"

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

bool GlobalInit::status() const noexcept
{
    return initStatus;
}

void GlobalInit::reinit() noexcept
{
    glfwTerminate();
    initStatus = glfwInit();
}

} // namespace GL3D