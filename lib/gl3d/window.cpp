#include "gl3d/window.h"

#include <private/global_init.h>
#include <stdexcept>

namespace GL3D
{

Window::Window(const std::uint16_t width, const std::uint16_t height, const std::string &title) : windowPtr(nullptr)
{
    if (GlobalInit::GetInstance())
        windowPtr = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    else
        throw std::runtime_error("Global context uninitialized");
}

Window::~Window() noexcept
{
    if (windowPtr)
        glfwDestroyWindow(windowPtr);
}

} // namespace GL3D
