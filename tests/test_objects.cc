#include <check.h>
#include <cstdlib>
#include <glm/ext/matrix_float4x4.hpp>

#include "core/objets/object.hh"
START_TEST(test_test)
{
    Playground::Core::Object obj{};
    glm::mat4 t = obj.getTransformMatrix();
    ck_assert(t == glm::mat4(1.0f));
}
END_TEST

Suite *test_objects_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("Objects");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_test);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s = test_objects_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
