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
    if (mock->expected_count > mock->actual_count) {
        // handle expected call


        // return expected return value
    } else {
        // handle unexpected calls

        // create memory zeroized memory block to return

    }
    return NULL;
}


#include "mock.h"
#include "test.h"


_MOCK_CREATE_MOCK(int, my_test_func, int, a);
_MOCK_CREATE_MOCK(void, test_void_function);
_MOCK_CREATE_MOCK(int, test, int, a, int, b);
int my_override(int a) {
    printf("Called with: %d", a);
}

void my_test() {
    int x = 5;
    EXPECT_CALL(my_test_func).WITH_ARGS(3).OVERRIDE(my_override);
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