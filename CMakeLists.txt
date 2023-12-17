cmake_minimum_required(VERSION 3.11)
project(OpenGL_Playground CXX)

set(CMAKE_CXX_STANDARD 17)

################################################################################
### REQUIREMENTS
################################################################################

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

################################################################################
### GLFW
################################################################################
add_subdirectory(externals/glfw)

################################################################################
### Imgui
################################################################################
file(GLOB IMGUI_SRC
		"externals/imgui/*.cpp"
		"externals/imgui/*.h"
)

################################################################################
### OpenGL_Playground build flags
################################################################################
set(PLAYGROUND_COMPILE_OPTIONS
	-Wall
	-Wextra
	-Werror
	-Wfloat-conversion
	-Woverloaded-virtual
	-Wnon-virtual-dtor
	"$<$<CONFIG:Debug>:-O0;-g>"
)

################################################################################
### include directories
################################################################################
include_directories(
	includes
	externals/glfw/include
	externals/imgui
	externals/imgui/backends
)

add_subdirectory(src)


################################################################################
### Testsuite
################################################################################
include(CTest)
add_subdirectory(tests)

################################################################################
### Executable
################################################################################
add_executable(OpenGL_Playground
	main.cc
	externals/imgui/backends/imgui_impl_glfw.cpp
	externals/imgui/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(OpenGL_Playground
	PRIVATE
		OpenGL::GL
		GLEW::GLEW
		glfw
		Playground
)
