#include <gl3d/window.h>
#include <iostream>
#include <stdexcept>

int main() noexcept
{
    try
    {
        GL3D::Window window(800, 600, "Test");
        window.exec();
    } catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
        return 1;
    }
    return 0;
}
