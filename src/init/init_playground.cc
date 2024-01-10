#include "init/init_gl.hh"
#include "init/init_glew.hh"

namespace Playground::Init
{

bool init_playground()
{
    return init_glew() && init_gl();
}

} // namespace Playground::Init
