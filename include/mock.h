//
// Created by Andrew Wade on 2019-01-06.
//

#ifndef TESTABLE_MOCK_H
#define TESTABLE_MOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../source/_mock.h"

#define CREATE_MOCK(return_type, function_name, args...) _MOCK_CREATE_MOCK(return_type, function_name, args)

#define EXPECT_CALL(function_name) _MOCK_EXPECT_CALL(function_name)

int test(int x);

CREATE_MOCK(int, test, int, x);

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_MOCK_H
