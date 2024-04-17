#pragma once

#include <cstdint>
#include <gl3d/utils/stack_pimpl.h>
#include <string>

namespace GL3D
{

class Window
{
private:
    struct WindowHolder;
    utils::stack_pimpl<WindowHolder, sizeof(void *), alignof(void *)> holder;

public:
    explicit Window(const std::uint16_t width, const std::uint16_t height, const std::string &title = "Window");

    void exec();
};

} // namespace GL3D
