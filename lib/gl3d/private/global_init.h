#pragma once

#include <GLFW/glfw3.h>
#include <private/singleton.h>

namespace GL3D
{

class GlobalInit : public Singleton<GlobalInit>
{
private:
    bool initStatus;

public:
    explicit GlobalInit(token) noexcept;
    ~GlobalInit() noexcept;

    bool status() const noexcept;
    void reinit() noexcept;
};

} // namespace GL3D
