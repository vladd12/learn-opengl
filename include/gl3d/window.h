#pragma once

#include <cstdint>
#include <string>

struct GLFWwindow;

namespace GL3D
{

class Window
{
private:
    GLFWwindow *windowPtr;

public:
    explicit Window(const std::uint16_t width, const std::uint16_t height, const std::string &title = "Window");
    ~Window() noexcept;
};

} // namespace GL3D
