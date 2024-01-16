#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>

#include "core/mesh/mesh.hh"
#include "core/program/program.hh"

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
    Object(glm::vec3 position, glm::quat rotation, glm::vec3 scale,
           std::shared_ptr<Mesh> mesh, std::shared_ptr<Program>);

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
    const glm::vec3 getForward();
    const glm::vec3 getUp();

    /**
     * TODO: Maybe refacto all of this in "traits" that can be inherited.
     * Like that we will be able to create differents types of objects depending
     * of which functionnalities we need them to have
     */
    // Render
public:
    void draw();

private:
    std::shared_ptr<Mesh> mesh_;
    std::shared_ptr<Program> program_;
};

} // namespace Playground::Core
