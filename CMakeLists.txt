cmake_minimum_required(VERSION 3.11)
project(OpenGL_Playground CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(externals/glfw)

include_directories(
	includes
	externals/imgui
	externals/glfw/include
)

file(GLOB IMGUI_SRC
		"externals/imgui/*.cpp"
	)

add_library(imgui_lib ${IMGUI_SRC})
target_compile_options(imgui_lib PUBLIC -Wall -Wextra -O2)

add_subdirectory(src)

option(COMPILE_TESTS "compile testsuite" OFF)

if (COMPILE_TESTS)
	include(CTest)
	add_subdirectory(tests)
endif(COMPILE_TESTS)
