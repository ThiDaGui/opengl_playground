#include <cstdlib>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

extern "C"
{
#include <check.h>
}

#include "core/objets/object.hh"

START_TEST(objects_origin)
{
    Playground::Core::Object obj{};
    glm::mat4 t = obj.getModelMatrix();
    ck_assert(t == glm::mat4(1.0f));
}
END_TEST

START_TEST(object_constuctor_position_vec3)
{
    Playground::Core::Object obj({ 1, 1, 1 }, { 1, 0, 0, 0 }, { 1, 1, 1 },
                                 nullptr, nullptr);
    glm::vec3 position = obj.getPosition();
    ck_assert(position == glm::vec3(1, 1, 1));
}
END_TEST

START_TEST(object_constuctor_position_mat4)
{
    Playground::Core::Object obj({ 1, 1, 1 }, { 1, 0, 0, 0 }, { 1, 1, 1 },
                                 nullptr, nullptr);
    glm::mat4 modelMatrix = obj.getModelMatrix();
    glm::mat4 ref = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1);

    ck_assert(modelMatrix == ref);
}
END_TEST

START_TEST(object_set_position_vec3)
{
    Playground::Core::Object obj{};
    obj.setPosition({ 1, 1, 1 });

    glm::vec3 position = obj.getPosition();
    glm::vec3 ref = { 1, 1, 1 };

    ck_assert(position == ref);
}
END_TEST

Suite *test_objects_suite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_position;
    s = suite_create("Objects");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, objects_origin);
    suite_add_tcase(s, tc_core);

    tc_position = tcase_create("Position");
    tcase_add_test(tc_position, object_constuctor_position_vec3);
    tcase_add_test(tc_position, object_constuctor_position_mat4);
    tcase_add_test(tc_position, object_set_position_vec3);
    suite_add_tcase(s, tc_position);

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
