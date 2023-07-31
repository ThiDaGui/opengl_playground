#pragma once

#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/mat4x4.hpp>

namespace Playground::Core
{

    class Object
    {
    protected:
        glm::vec3 position_;
        glm::quat rotation_;
        glm::vec3 scale_;

    public:
        Object() = default;

        void setPosition(glm::vec3 &position);
        glm::vec3 getPosition();

        void move(glm::vec3 &other);

        void setRotation(glm::quat &rotation);
        void setRotation(glm::vec3 &euler_rotation);
        glm::quat getRotation();

        void setScale(glm::vec3 &scale);
        glm::vec3 getScale();
    };

} // namespace Playground::Core
