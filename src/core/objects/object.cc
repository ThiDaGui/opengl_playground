#include "core/objets/object.hh"

#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>

namespace Playground::Core
{

    void Object::setPosition(glm::vec3 &position)
    {
        position_ = position;
    }

    glm::vec3 Object::getPosition()
    {
        return position_;
    }

    void Object::move(glm::vec3 &other)
    {
        position_ += other;
    }

    void Object::setRotation(glm::quat &rotation)
    {
        rotation_ = rotation;
    }

    void Object::setRotation(glm::vec3 &euler_rotation)
    {
        rotation_ = glm::quat(euler_rotation);
    }

    glm::quat Object::getRotation()
    {
        return rotation_;
    }

    void Object::setScale(glm::vec3 &scale)
    {
        scale_ = scale;
    }

    glm::vec3 Object::getScale()
    {
        return scale_;
    }

} // namespace Playground::Core
