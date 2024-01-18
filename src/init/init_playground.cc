#include "init/init_playground.hh"

#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "core/mesh/mesh.hh"
#include "imgui.h"

namespace Playground::Init
{

bool init_glew()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "GLEW error: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    return true;
}
static float delta_time = 0.0f;

static auto const start_time = std::chrono::high_resolution_clock::now();

float program_time()
{
    auto const current_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float, std::chrono::seconds::period>(
               current_time - start_time)
        .count();
}
void update_delta_time()
{
    static double time = 0.0;
    const double new_time = program_time();
    delta_time = float(new_time - time);
    time = new_time;
}

void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id,
                                 GLenum severity, GLsizei length,
                                 GLchar const *message, void const *user_param)
{
    (void)length;
    (void)user_param;

    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;

    auto const src_str = [source]() {
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "WINDOW SYSTEM";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "SHADER COMPILER";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "THIRD PARTY";
        case GL_DEBUG_SOURCE_APPLICATION:
            return "APPLICATION";
        case GL_DEBUG_SOURCE_OTHER:
            return "OTHER";
        default:
            return "UNKNOWN SOURCE";
        }
    }();

    auto const type_str = [type]() {
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            return "ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PORTABILITY:
            return "PORTABILITY";
        case GL_DEBUG_TYPE_PERFORMANCE:
            return "PERFORMANCE";
        case GL_DEBUG_TYPE_MARKER:
            return "MARKER";
        case GL_DEBUG_TYPE_OTHER:
            return "OTHER";
        default:
            return "UNKNOWN TYPE";
        }
    }();

    auto const severity_str = [severity]() {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return "NOTIFICATION";
        case GL_DEBUG_SEVERITY_LOW:
            return "LOW";
        case GL_DEBUG_SEVERITY_MEDIUM:
            return "MEDIUM";
        case GL_DEBUG_SEVERITY_HIGH:
            return "HIGH";
        default:
            return "UNKNOWN SEVERITY";
        }
    }();
    std::cout << src_str << ", " << type_str << ", " << severity_str << ", "
              << id << ": " << message << '\n';
}

bool init_gl()
{
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(message_callback, 0);
#endif

    static GLuint global_vao;
    glGenVertexArrays(1, &global_vao);
    glBindVertexArray(global_vao);

    return true;
}

void glfw_print_error()
{
    const char *err = nullptr;
    glfwGetError(&err);
    std::cerr << "GLFW error: " << err << std::endl;
}

bool init_glfw(InitStruct &init_struct)
{
    if (!glfwInit())
    {
        glfw_print_error();
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!(init_struct.window = glfwCreateWindow(
              init_struct.window_size.x, init_struct.window_size.y,
              "Playground", nullptr, nullptr)))
    {
        glfw_print_error();
        return false;
    }
    glfwMakeContextCurrent(init_struct.window);
    glfwSwapInterval(1);

    return true;
}

bool init_imgui(const InitStruct &init_struct)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= init_struct.config_flags;
    if (init_struct.config_flags & ImGuiConfigFlags_ViewportsEnable)
        io.ConfigViewportsNoAutoMerge = true;

    ImGui_ImplGlfw_InitForOpenGL(init_struct.window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    return true;
}

void process_input(GLFWwindow *window, Playground::Core::LookAtCamera &camera)
{
    static glm::dvec2 mouse_pos;

    glm::dvec2 new_mouse_pos;
    glfwGetCursorPos(window, &new_mouse_pos.x, &new_mouse_pos.y);
    {
        glm::vec3 mouvement = {};
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            mouvement += camera.getForward();
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            mouvement -= camera.getForward();
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            mouvement += camera.getRight();
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            mouvement -= camera.getRight();

        float speed = 10.0f;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            speed *= 5.0f;

        if (glm::length(mouvement) > 0.0f)
        {
            const glm::vec3 new_pos =
                camera.getPosition() + mouvement * speed * delta_time;
            camera.setViewMatrix(new_pos, new_pos + camera.getForward(),
                                 camera.getUp());
        }
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        const glm::vec2 delta =
            glm::vec2(mouse_pos - new_mouse_pos) * (float)M_PI / 360.0f;
        if (glm::length(delta) > 0.0f)
        {
            glm::mat4 rotation_matrix = glm::rotate(
                glm::mat4(1.0f), delta.x, glm::vec3(0.0f, 0.0f, 1.0f));
            rotation_matrix =
                glm::rotate(rotation_matrix, delta.y, camera.getRight());
            camera.setViewMatrix(
                camera.getPosition(),
                camera.getPosition()
                    + (glm::mat3(rotation_matrix) * camera.getForward()),
                (glm::mat3(rotation_matrix) * camera.getUp()));
        }
    }
    mouse_pos = new_mouse_pos;
}

bool init_playground(InitStruct &init_struct)
{
    if (init_glfw(init_struct) && init_glew() && init_gl()
        && init_imgui(init_struct))
    {
        std::cout << "OpenGL initialized\n"
                  << std::setw(4) << ""
                  << "Version: " << glGetString(GL_VERSION) << '\n'
                  << std::setw(4) << ""
                  << "Vendor: " << glGetString(GL_VENDOR) << '\n'
                  << std::setw(4) << ""
                  << "Renderer: " << glGetString(GL_RENDERER) << '\n';
        return true;
    }
    return false;
}

} // namespace Playground::Init
