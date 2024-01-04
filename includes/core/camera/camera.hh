#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace Playground::Core
{

class Camera
{
protected:
    glm::mat4 projection_matrix_;

public:
    Camera() = default;
    virtual ~Camera() = default;

    virtual const glm::mat4 getViewMatrix() = 0;

    const glm::mat4 getProjectionMatrix();
    void setProjectionMatrix(const glm::mat4 &projection_matrix);
    void setProjectionMatrix(const float aspect_ratio,
                             const float field_of_view, const float z_near,
                             const float z_far);
};

} // namespace Playground::Core
