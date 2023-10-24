#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>

namespace Playground::Core
{

    class Object
    {
    protected:
        glm::vec3 position_;
        glm::quat rotation_;
        glm::vec3 scale_;

    public:
        Object();
        Object(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

        // Position
    public:
        void setPosition(glm::vec3 const &position);
        const glm::vec3 getPosition();

        void move(glm::vec3 const &other);

        const glm::mat4 getTranslationMatrix();
        const glm::mat4 getInverseTranslationMatrix();

        // Rotation
    public:
        void setRotation(glm::quat const &rotation);
        void setRotation(glm::vec3 const &euler_angles);
        const glm::quat getRotation();

        const glm::mat4 getRotationMatrix();
        const glm::mat4 getInverseRotationMatrix();

        // Scale
    public:
        void setScale(glm::vec3 const &scale);
        const glm::vec3 getScale();

        const glm::mat4 getScaleMatrix();
        const glm::mat4 getInverseScaleMatrix();

        // Transformation Matrix
    public:
        const glm::mat4 getModelMatrix();
        const glm::mat4 getInverseModelMatrix();

        // Utils
    public:
        const glm::vec3 getRight();
        const glm::vec3 getFront();
        const glm::vec3 getUp();

        //         // Rendering
        //     protected:
        //         virtual void preRender() = 0;
        //         virtual void postRender() = 0;
        //
        //     public:
        //         virtual void render() = 0;
    };

} // namespace Playground::Core
