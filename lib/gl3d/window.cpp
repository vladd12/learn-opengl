#include "gl3d/window.h"

// NOTE: GLAD library header must be included before
// other header files that require OpenGL (like GLFW).
// clang-format off
#include <glad/glad.h>
// clang-format on

#include <GLFW/glfw3.h>
#include <gl3d/global_init.h>
#include <stdexcept>

namespace
{

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

}

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

Window::Window(const std::uint16_t width, const std::uint16_t height, const std::string &title)
{
    if (!GlobalInit::GetInstance())
        throw std::runtime_error("Global context uninitialized");

    auto holder = storage.start_lifetime_as<WindowHolder>(nullptr);
    *holder = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!(*holder))
    {
        destroy_holder();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(*holder);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        destroy_holder();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(*holder, framebuffer_size_callback);
}

void Window::destroy_holder() noexcept
{
    storage.end_lifetime_as<WindowHolder>();
}

Window::~Window() noexcept
{
    destroy_holder();
}

void Window::exec()
{
    auto holder = storage.get_object_from_storage<WindowHolder>();
    while (!glfwWindowShouldClose(*holder))
    {
        // check and call events and swap the buffers
        glfwSwapBuffers(*holder);
        glfwPollEvents();
    }
}

} // namespace GL3D
