//
// Created by Andrew Wade on 6/25/18.
//

#include "test/_node_test.h"
#include "stdio.h"



#include "mockable.h"
#include "test.h"


CREATE_MOCK(int, my_test_func, int, a);
CREATE_MOCK(void, test_void_function);
CREATE_MOCK(int, test, void);

void my_override(int a) {
    printf("Called with: %d", a);
}

void my_test() {
    int x                                             = 5;
    EXPECT_CALL(my_test_func).WITH_ARGS(3).CALLBACK(my_override);
    EXPECT_CALL(my_test_func).WITH_ARGS(3).RETURNS(3);
    EXPECT_CALL(my_test_func).WITH_ARGS(3).TIMES(3);
    EXPECT_CALL(test_void_function).TIMES(3);

    int resp = test_my_test_func(3);
    test_void_function();
    printf("resp=%d", resp);
}


int main() {
    my_test();
    return 0;
}