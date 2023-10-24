#include "core/objets/object.hh"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

namespace Playground::Core
{

    Object::Object()
        : position_(0, 0, 0)
        , rotation_(1.0f, 0.0f, 0.0f, 0.0f)
        , scale_(1.0f)
    {}

    Object::Object(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
        : position_(position)
        , rotation_(rotation)
        , scale_(scale)
    {}

    // Position
    void Object::setPosition(glm::vec3 const &position)
    {
        position_ = position;
    }

    const glm::vec3 Object::getPosition()
    {
        return position_;
    }

    void Object::move(glm::vec3 const &other)
    {
        position_ += other;
    }

    const glm::mat4 Object::getTranslationMatrix()
    {
        glm::mat4 mat = glm::translate(position_);
        return mat;
    }

    const glm::mat4 Object::getInverseTranslationMatrix()
    {
        glm::mat4 mat = glm::translate(-position_);
        return mat;
    }

    // Rotation
    void Object::setRotation(glm::quat const &rotation)
    {
        rotation_ = rotation;
    }

    void Object::setRotation(glm::vec3 const &euler_angle)
    {
        rotation_ = glm::quat(euler_angle);
    }

    const glm::quat Object::getRotation()
    {
        return rotation_;
    }

    const glm::mat4 Object::getRotationMatrix()
    {
        glm::mat4 mat = glm::mat4_cast(rotation_);
        return mat;
    }

    const glm::mat4 Object::getInverseRotationMatrix()
    {
        glm::mat4 mat = glm::mat4_cast(glm::conjugate(rotation_));
        return mat;
    }

    // Scale
    void Object::setScale(glm::vec3 const &scale)
    {
        scale_ = scale;
    }

    const glm::vec3 Object::getScale()
    {
        return scale_;
    }

    const glm::mat4 Object::getScaleMatrix()
    {
        glm::mat4 mat = glm::scale(scale_);
        return mat;
    }

    const glm::mat4 Object::getInverseScaleMatrix()
    {
        glm::mat4 mat = glm::scale(1.0f / scale_);
        return mat;
    }

    // Transformation

    const glm::mat4 Object::getModelMatrix()
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::scale(modelMatrix, scale_);
        modelMatrix = glm::rotate(modelMatrix, glm::angle(rotation_),
                                  glm::axis(rotation_));
        modelMatrix = glm::translate(modelMatrix, position_);

        return modelMatrix;
    }

    const glm::mat4 Object::getInverseModelMatrix()
    {
        return getInverseScaleMatrix() * getInverseRotationMatrix()
            * getInverseTranslationMatrix();
    }

} // namespace Playground::Core
