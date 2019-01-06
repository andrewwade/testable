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




_MOCK_CREATE_MOCK(int, test_function, int, a1, int, a2);
_MOCK_CREATE_MOCK(void, test_void_function, char*, s);


void my_test() {
    EXPECT_CALL(test_function).WITH_ARGS(3, 2).RETURNS(3);
    EXPECT_CALL(test_function).WITH_ARGS(3, 2).TIMES(3);

    test_function(1, 2);
}


int main() {
    my_test();
}