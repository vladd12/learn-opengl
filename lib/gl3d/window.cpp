#include "gl3d/window.h"

#include <GLFW/glfw3.h>
#include <gl3d/global_init.h>
#include <stdexcept>

namespace GL3D
{

struct Window::WindowHolder
{
private:
    GLFWwindow *fd;

    inline void destroy() noexcept
    {
        if (fd)
            glfwDestroyWindow(fd);
    }

public:
    inline explicit WindowHolder(GLFWwindow *ptr) noexcept : fd(ptr)
    {
    }

    inline ~WindowHolder() noexcept
    {
        destroy();
    }

    inline WindowHolder &operator=(GLFWwindow *ptr) noexcept
    {
        destroy();
        fd = ptr;
        return *this;
    }

    inline operator bool() noexcept
    {
        return fd;
    }

    inline operator GLFWwindow *() noexcept
    {
        return fd;
    }
};

Window::Window(const std::uint16_t width, const std::uint16_t height, const std::string &title) : holder(nullptr)
{
    if (!GlobalInit::GetInstance())
        throw std::runtime_error("Global context uninitialized");

    *holder = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
}

} // namespace GL3D
