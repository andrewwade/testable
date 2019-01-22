//
// Created by Andrew Wade on 2019-01-20.
//
#include "_mock_tests.h"
#include "mockable.h"




#include <byte_pool.h>
#include <block_pool.h>
#include "stdio.h"
#include "mockable.h"
#include "_mock_tests.h"


uint8_t byte_buffer[2048];
byte_pool_t byte_pool;

uint8_t call_buffer[2048];
block_pool_t call_pool;

byte_pool_t *mock_byte_pool;
block_pool_t *mock_call_pool;

int test_my_test_func(int value) {
    return my_test_func(value);
}

CREATE_MOCK(int, my_test_func, int, a);
CREATE_MOCK(void, test_void_function);
CREATE_MOCK(int, test, void);

int callback_param;

void my_override(int a) {
    callback_param = a;
}

TEST(_mock_test_setup) {
    callback_param = -1;
}

TEST(_mock_test_teardown) {

}

TEST(_mock_returns_correct_value) {
    int result;
    EXPECT_CALL(my_test_func).WITH_ARGS(3).CALLBACK(my_override).RETURNS(3);
    EXPECT_CALL(my_test_func).WITH_ARGS(8).RETURNS(5);
    EXPECT_CALL(my_test_func).WITH_ARGS(3).TIMES(3);
    EXPECT_CALL(test_void_function).TIMES(3);

    result = test_my_test_func(8);
    ASSERT_INT_EQ(5, result, "Response should be 5");

    ASSERT_INT_EQ(-1, callback_param, "Should not call callback");

    result = test_my_test_func(3);
    ASSERT_INT_EQ(3, result, "Response should be 3");

    ASSERT_INT_EQ(3, callback_param, "Wrong callback parameter");
}

TEST_GROUP(mock_tests) {
    TEST_SETUP(_mock_test_setup);
    TEST_TEARDOWN(_mock_test_teardown);
    TEST_CASE(_mock_returns_correct_value);
}
