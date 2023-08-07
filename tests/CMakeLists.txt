find_package(PkgConfig)
pkg_check_modules(CHECK REQUIRED check)

add_executable(test_objects test_objects.cc)

target_link_libraries(test_objects
	PUBLIC
		Playground
		glm::glm
		${CHECK_LDFLAGS}
)

add_test(NAME test_objects COMMAND test_objects)
