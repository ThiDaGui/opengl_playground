#pragma once

#include <GL/glew.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <iostream>

#include "core/camera/look_at_camera.hh"

namespace Playground::Init
{

struct InitStruct
{
    GLFWwindow *window = nullptr;
    glm::uvec2 window_size = { 640, 480 };
    int config_flags = ImGuiConfigFlags_NavEnableKeyboard
        | ImGuiConfigFlags_NavEnableGamepad | ImGuiConfigFlags_DockingEnable
        | ImGuiConfigFlags_ViewportsEnable;

    InitStruct() = default;
    InitStruct(const InitStruct &) = delete;
    InitStruct &operator=(const InitStruct &) = delete;
    InitStruct(InitStruct &&) = default;
    InitStruct &operator=(InitStruct &&) = default;

    ~InitStruct()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

void process_input(GLFWwindow *window, Playground::Core::LookAtCamera &camera,
                   float delta_time);

bool init_playground(InitStruct &init_struct);

} // namespace Playground::Init
