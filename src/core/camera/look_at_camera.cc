#include "core/camera/look_at_camera.hh"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>

#include "core/camera/camera.hh"

namespace Playground::Core
{



static glm::vec3 return_forward(const glm::mat4 &view_matrix)
{
    return -glm::normalize(
        glm::vec3(view_matrix[0][2], view_matrix[1][2], view_matrix[2][2]));
}

static glm::vec3 return_right(const glm::mat4 &view_matrix)
{
    return glm::normalize(
        glm::vec3(view_matrix[0][0], view_matrix[1][0], view_matrix[2][0]));
}

static glm::vec3 return_up(const glm::mat4 &view_matrix)
{
    return glm::normalize(
        glm::vec3(view_matrix[0][1], view_matrix[1][1], view_matrix[2][1]));
}

LookAtCamera::LookAtCamera(glm::vec3 position, glm::vec3 look_at, glm::vec3 up)
    : Camera()
    , up_(up)
    , position_(position)
    , look_at_(look_at)
{}

const glm::mat4 LookAtCamera::getViewMatrix()
{
    return glm::lookAt(position_, look_at_, up_);
}

void LookAtCamera::setViewMatrix(const glm::vec3 position,
                                 const glm::vec3 look_at, const glm::vec3 up)
{
    position_ = position;
    look_at_ = look_at;
    up_ = up;
}

const glm::vec3 LookAtCamera::getPosition()
{
    return position_;
}

void LookAtCamera::setPosition(const glm::vec3 position)
{
    position_ = position;
}

glm::vec3 LookAtCamera::getUp()
{
    return return_up(getViewMatrix());  
}

glm::vec3 LookAtCamera::getRight()
{
    return return_right(getViewMatrix());
}

glm::vec3 LookAtCamera::getForward()
{
    return return_forward(getViewMatrix());
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
