#include "core/objets/object.hh"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <memory>

#include "core/mesh/mesh.hh"

namespace Playground::Core
{

Object::Object()
    : position_(0, 0, 0)
    , rotation_(1.0f, 0.0f, 0.0f, 0.0f)
    , scale_(1.0f)
{}

Object::Object(glm::vec3 position, glm::quat rotation, glm::vec3 scale,
               std::shared_ptr<Mesh> mesh, std::shared_ptr<Program> program)
    : position_(position)
    , rotation_(rotation)
    , scale_(scale)
    , mesh_(mesh)
    , program_(program)
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
    return getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
}

const glm::mat4 Object::getInverseModelMatrix()
{
    return getInverseScaleMatrix() * getInverseRotationMatrix()
        * getInverseTranslationMatrix();
}

const glm::vec3 Object::getRight()
{
    return glm::normalize(getModelMatrix() * glm::vec4{ 1.0, 0.0, 0.0, 1.0 });
}

const glm::vec3 Object::getForward()
{
    return glm::normalize(getModelMatrix() * glm::vec4{ 0.0, 1.0, 0.0, 1.0 });
}

const glm::vec3 Object::getUp()
{
    return glm::normalize(getModelMatrix() * glm::vec4{ 0.0, 0.0, 1.0, 1.0 });
}

void Object::draw()
{
    program_->bind();
    program_->set_uniform("model", getModelMatrix());
    mesh_->draw();
}

} // namespace Playground::Core
