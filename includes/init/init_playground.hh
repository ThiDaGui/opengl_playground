#pragma once

#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <iostream>

namespace Playground::Init
{

struct InitStruct
{
    GLFWwindow *window = nullptr;
    glm::uvec2 window_size = { 640, 480 };

    InitStruct() = default;
    InitStruct(const InitStruct &) = delete;
    InitStruct &operator=(const InitStruct &) = delete;
    InitStruct(InitStruct &&) = default;
    InitStruct &operator=(InitStruct &&) = default;

    ~InitStruct()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

bool init_playground(InitStruct &init_struct);

} // namespace Playground::Init
