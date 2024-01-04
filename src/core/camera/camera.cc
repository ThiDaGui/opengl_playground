#include "core/camera/camera.hh"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Playground::Core
{
const glm::mat4 Camera::getProjectionMatrix()
{
    return projection_matrix_;
}

void Camera::setProjectionMatrix(const glm::mat4 &projection_matrix)
{
    projection_matrix_ = projection_matrix;
}

void Camera::setProjectionMatrix(const float aspect_ratio,
                                 const float field_of_view, const float z_near,
                                 const float z_far)
{
    projection_matrix_ =
        glm::perspective(field_of_view, aspect_ratio, z_near, z_far);
}

} // namespace Playground::Core
