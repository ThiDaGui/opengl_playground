cmake_minimum_required(VERSION 3.11)
project(OpenGL_Playground CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(externals/glfw)
include_directories(externals/glfw/include externals/imgui/ externals/imgui/backends)

set(PLAYGROUND_COMPILE_OPTIONS
	-Wall -Wextra -Werror -Wfloat-conversion -Woverloaded-virtual -Wnon-virtual-dtor
	"$<$<CONFIG:Debug>:-O0;-g>")

include_directories(
	includes
)

file(GLOB IMGUI_SRC
		"externals/imgui/*.cpp"
		"externals/imgui/*.h"
	)

add_subdirectory(src)

include(CTest)
add_subdirectory(tests)

add_executable(OpenGL_Playground main.cc externals/imgui/backends/imgui_impl_glfw.cpp externals/imgui/backends/imgui_impl_opengl3.cpp)
target_link_libraries(OpenGL_Playground
	PRIVATE
		OpenGL::GL
		GLEW::GLEW
		glfw
		Playground
	)
