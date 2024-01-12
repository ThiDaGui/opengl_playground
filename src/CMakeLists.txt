set(PLAYGROUND_COMPILE_OPTIONS
	-Wall -Wextra -Werror -Wfloat-conversion -Woverloaded-virtual -Wnon-virtual-dtor
	"$<$<CONFIG:Debug>:-O0;-g>")

file(GLOB_RECURSE PLAYGROUND_SRC
	"*.cc"
)

add_library(Playground "${PLAYGROUND_SRC}")
target_compile_options(Playground PUBLIC
	"${PLAYGROUND_COMPILE_OPTIONS}")

target_link_libraries(Playground
	PUBLIC
		OpenGL::OpenGL
		GLEW::GLEW
		glm::glm
		imgui_lib
		glfw
)
