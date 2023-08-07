#include "core/objets/object.hh"

namespace Playground::Core
{

    Object::Object()
        : position_(0, 0, 0)
        , rotation_(1.0f, 0.0f, 0.0f, 0.0f)
        , scale_(1.0f)
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
        return glm::translate(glm::mat4(1.0f), position_);
    }

    const glm::mat4 Object::getInverseTranslationMatrix()
    {
        return glm::translate(glm::mat4(1.0f), -position_);
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
        return glm::mat4_cast(rotation_);
    }

    const glm::mat4 Object::getInverseRotationMatrix()
    {
        return glm::mat4_cast(glm::conjugate(rotation_));
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
        return glm::scale(glm::mat4(1.0f), scale_);
    }

    const glm::mat4 Object::getInverseScaleMatrix()
    {
        return glm::scale(glm::mat4(1.0f), 1.0f / scale_);
    }

    // Transformation

    const glm::mat4 Object::getTransformMatrix()
    {
        return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
    }

    const glm::mat4 Object::getInverseTransformMatrix()
    {
        return getInverseScaleMatrix() * getInverseRotationMatrix()
            * getInverseTranslationMatrix();
    }

} // namespace Playground::Core
