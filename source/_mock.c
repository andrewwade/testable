//
// Created by Andrew Wade on 12/8/18.
//


#include "_mock.h"


void *_mock_call(_mock_t *mock, _mock_variable_t *args, int count) {
    printf("%s %s(", mock->return_value.type, mock->name);
    for (int i = 0; i < mock->arguments_count; i++) {
        _mock_variable_t *arg = &mock->arguments[i];
        printf("%s %s,", arg->value.type, arg->name);
    }
    printf("):\n");
    if (mock->expected_call_count > mock->received_call_count) {
        // handle expected call


        // return expected return value
    } else {
        // handle unexpected calls

        // create memory zeroized memory block to return

    }
    return NULL;
}

void _mock_expect_call(_mock_t *mock) {
    // TODO: create new _mock_call_t in expected queue

    // TODO: set default values

    // TODO: increment expected count by 1
}

void _mock_expect_call_callback(_mock_t *mock, void *override) {
    mock->callback = override;
}

void _mock_expect_call_with_args(_mock_t *mock, _mock_variable_t *args, int count) {

}

void _mock_expect_call_returns(_mock_t *mock, _mock_value_t return_value) {

}

void _mock_expect_call_times(_mock_t *mock, int times) {

}


#include "mock.h"
#include "test.h"


_MOCK_CREATE_MOCK(int, my_test_func, int, a);
_MOCK_CREATE_MOCK(void, test_void_function);
_MOCK_CREATE_MOCK(int, test, void);

void my_override(int a) {
    printf("Called with: %d", a);
}

void my_test() {
    int x = 5;
    EXPECT_CALL(my_test_func).WITH_ARGS(3).CALLBACK(my_override);
    EXPECT_CALL(my_test_func).WITH_ARGS(3).RETURNS(3);
    EXPECT_CALL(my_test_func).WITH_ARGS(3).TIMES(3);
    EXPECT_CALL(test_void_function).TIMES(3);

    _MOCK_NAME(my_test_func).return_value.address = & x;
    int resp = test_my_test_func(3);
    test_void_function();
    printf("resp=%d", resp);
}


int main() {
    my_test();
    return 0;
}