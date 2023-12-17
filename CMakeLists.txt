cmake_minimum_required(VERSION 3.11)
project(OpenGL_Playground CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

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
