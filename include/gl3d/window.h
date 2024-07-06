#pragma once

#include <cstdint>
#include <gl3d/utils/aligned_storage.h>
#include <gl3d/utils/stack_pimpl.h>
#include <string>

namespace GL3D
{

class Window
{
private:
    struct WindowHolder;
    utils::aligned_storage<sizeof(void *), alignof(void *)> storage;

public:
    explicit Window(const std::uint16_t width, const std::uint16_t height, const std::string &title = "Window");
    ~Window() noexcept;

    void exec();
};

} // namespace GL3D
