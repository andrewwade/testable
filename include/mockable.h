//
// Created by Andrew Wade on 2019-01-06.
//

#ifndef TESTABLE_MOCKABLE_H
#define TESTABLE_MOCKABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../src/_mock.h"

#define CREATE_MOCK_VALUE(type, name) _mock_value_t _mock_##name = _MOCK_VALUE(type)

#define CREATE_MOCK_VARIABLE(type, name) _mock_variable_t _mock_##name = _MOCK_VARIABLE(type, name);

#define CREATE_MOCK(return_type, function_name, args...) _MOCK_CREATE_MOCK(return_type, function_name, args)

#define MOCK_SETUP(function_name) _MOCK_SETUP(function_name)

#define MOCK_TEARDOWN(function_name) _MOCK_TEARDOWN(function_name)

#define EXPECT_CALL(function_name) _MOCK_EXPECT_CALL(function_name)

#define GET_MOCK(function_name) _MOCK_GET_MOCK(function_name)
#ifdef __cplusplus
};
#endif

#endif //TESTABLE_MOCK_H
