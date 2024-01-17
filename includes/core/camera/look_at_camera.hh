#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

#include "core/camera/camera.hh"

namespace Playground::Core
{

class LookAtCamera : public Camera
{
private:
    glm::vec3 up_;
    glm::vec3 position_;
    glm::vec3 look_at_;
    glm::mat4 view_matrix_;

public:
    LookAtCamera();
    LookAtCamera(glm::vec3 up);
    LookAtCamera(glm::vec3 up, glm::vec3 position, glm::vec3 look_at);

    virtual const glm::mat4 getViewMatrix() override;
    void setViewMatrix(const glm::vec3 position, const glm::vec3 look_at,
                       const glm::vec3 up);
    void setViewMatrix(const glm::mat4 view_matrix);

    const glm::vec3 getPosition();
    void setPosition(const glm::vec3 position);

    glm::vec3 getUp();
    glm::vec3 getRight();
    glm::vec3 getForward();

    const glm::vec3 getLookAt();
    void setLookAt(const glm::vec3 look_at);

};

} // namespace Playground::Core
