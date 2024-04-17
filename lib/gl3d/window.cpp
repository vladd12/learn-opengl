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

    /// \brief Destroys stored pointer if it's not NULL>
    inline void destroy() noexcept
    {
        if (fd)
            glfwDestroyWindow(fd);
    }

public:
    /// \brief Default c-tor.
    inline explicit WindowHolder(GLFWwindow *ptr) noexcept : fd(ptr)
    {
    }

    /// \brief Default d-tor.
    inline ~WindowHolder() noexcept
    {
        destroy();
    }

    /// \brief Assignment operator for updating stored window pointer.
    inline WindowHolder &operator=(GLFWwindow *ptr) noexcept
    {
        destroy();
        fd = ptr;
        return *this;
    }

    /// \brief Checks the current pointer stored in object.
    inline operator bool() noexcept
    {
        return fd;
    }

    /// \brief Returns the stored pointer.
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
    if (!(*holder))
        throw std::runtime_error("Failed to create GLFW window");
    glfwMakeContextCurrent(*holder);
}

void Window::exec()
{
    while (!glfwWindowShouldClose(*holder))
    {
        // check and call events and swap the buffers
        glfwSwapBuffers(*holder);
        glfwPollEvents();
    }
}

} // namespace GL3D
