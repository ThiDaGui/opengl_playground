add_library(Playground init/init_gl.cc core/shader/shader.cc utils/io/io.cc
core/objects/object.cc)

target_link_libraries(Playground PUBLIC
	glm::glm
)
