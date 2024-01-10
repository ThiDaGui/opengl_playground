#include <GL/glew.h>
#include <iostream>

namespace Playground::Init
{

bool init_glew()
{
    if (glewInit())
    {
        std::cerr << "Error while initializing glew";
        return false;
    }
    return true;
}

} // namespace Playground::Init
