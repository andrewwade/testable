//
// Created by Andrew Wade on 6/29/18.
//

#ifndef TESTABLE_TESTS_H
#define TESTABLE_TESTS_H

#include "../src/_test.h"

#ifdef __cplusplus
extern "C" {
#endif

/** declare a test with execution body */
#define TEST(name)                                          \
void _test_##name##_function(_test_t *test)

#define RUN_TEST(name)                                      \
_test_t _test_##name = {                                    \
    #name,                                                  \
    0,                                                      \
    NULL,                                                   \
    0,                                                      \
    &_test_##name##_function                                \
    };                                                      \
_test_##name##_function(&_test_##name)

/* test case control */
#if TEST_SUPPORT_VARIADIC_MACROS

#define TEST_FAIL(message...) ASSERT_CHAR_EQ(0, 1, "Test Failed")
#define TEST_SKIP(message...)

#else /* TEST_VARIADIC_MACROS_SUPPORTED == 0 */

#define TEST_FAIL_MESSAGE(message)
#define TEST_FAIL()

#define TEST_SKIP_MESSAGE(message)
#define TEST_SKIP()

#endif /* TEST_VARIADIC_MACROS_SUPPORTED */

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_TEST_H
