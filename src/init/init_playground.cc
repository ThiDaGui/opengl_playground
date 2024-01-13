#include "init/init_playground.hh"

#include <glm/vec2.hpp>
#include <iomanip>
#include <iostream>

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

    return true;
}

bool init_playground(InitStruct &init_struct)
{
    if (init_glfw(init_struct) && init_glew() && init_gl())
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
