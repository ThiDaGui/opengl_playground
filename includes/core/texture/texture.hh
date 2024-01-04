#include <GL/gl.h>
#include <glm/fwd.hpp>

namespace Playground::Core
{
class Texture
{
public:
    Texture() = default;
    Texture(const glm::uvec2 &size);

private:
    GLuint gl_texture_;
};
} // namespace Playground::Core
