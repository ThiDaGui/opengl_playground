cmake_minimum_required(VERSION 3.11)
project(OpenGL_Playground CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_compile_options(-Wall -Wextra -Werror
	"$<$<CONFIG:Debug>:-O0;-g>")

include_directories(
	includes
)

add_subdirectory(src)

include(CTest)
add_subdirectory(tests)
