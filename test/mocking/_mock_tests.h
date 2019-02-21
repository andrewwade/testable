//
// Created by Andrew Wade on 2019-01-20.
//

#ifndef TESTABLE_MOCK_TEST_H
#define TESTABLE_MOCK_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "clarity/testing.h"

TEST_GROUP(mock_tests);

int my_test_func(int a);

int test_my_test_func(int val);


#ifdef __cplusplus
};
#endif

#endif //TESTABLE_MOCK_TEST_H
