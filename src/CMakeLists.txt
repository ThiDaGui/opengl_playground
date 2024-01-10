file(GLOB_RECURSE PLAYGROUND_SRC
	"*.cc"
)

add_library(Playground "${PLAYGROUND_SRC}" "${IMGUI_SRC}")
target_compile_options(Playground PUBLIC
	"${PLAYGROUND_COMPILE_OPTIONS}")

target_link_libraries(Playground PUBLIC OpenGL::OpenGL GLEW::GLEW glm::glm)
