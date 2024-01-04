#include "core/camera/look_at_camera.hh"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>

namespace Playground::Core
{
LookAtCamera::LookAtCamera()
    : up_(0, 0, 1)
    , position_(0, 0, 0)
    , look_at_(1, 0, 0)
{}

LookAtCamera::LookAtCamera(glm::vec3 up)
    : up_(up)
    , position_(0, 0, 0)
    , look_at_(1, 0, 0)
{}

LookAtCamera::LookAtCamera(glm::vec3 up, glm::vec3 position, glm::vec3 look_at)
    : up_(up)
    , position_(position)
    , look_at_(look_at)
{}

const glm::mat4 LookAtCamera::getViewMatrix()
{
    return glm::lookAt(position_, look_at_, up_);
}

void LookAtCamera::setViewMatrix(const glm::vec3 position,
                                 const glm::vec3 look_at)
{
    position_ = position;
    look_at_ = look_at;
}

const glm::vec3 LookAtCamera::getPosition()
{
    return position_;
}

void LookAtCamera::setPosition(const glm::vec3 position)
{
    position_ = position;
}

const glm::vec3 LookAtCamera::getLookAt()
{
    return look_at_;
}

void LookAtCamera::setLookAt(const glm::vec3 look_at)
{
    look_at_ = look_at;
}

} // namespace Playground::Core
