#pragma once

#include <gl3d/utils/singleton.h>

namespace GL3D
{

/// \brief Global GLFW context object.
class GlobalInit final : public Singleton<GlobalInit>
{
private:
    bool initStatus;

public:
    /// \brief Default c-tor.
    explicit GlobalInit(token) noexcept;
    /// \brief D-tor.
    ~GlobalInit() noexcept;

    /// \brief Closes current context and opens new GLFW context.
    void reinit() noexcept;

    /// \brief Checking global context.
    operator bool() const noexcept;
};

} // namespace GL3D
