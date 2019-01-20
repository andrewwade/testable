//
// Created by Andrew Wade on 6/25/18.
//

#include <byte_pool.h>
#include <block_pool.h>
#include "test/_node_test.h"
#include "stdio.h"



#include "mockable.h"
#include "test.h"

uint8_t byte_buffer[2048];
byte_pool_t byte_pool;

uint8_t call_buffer[2048];
block_pool_t call_pool;

byte_pool_t *mock_byte_pool;
block_pool_t *mock_call_pool;


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
    mock_call_pool = &call_pool;
    mock_byte_pool = &byte_pool;

    byte_pool_init(mock_byte_pool, byte_buffer, 2048);
    block_pool_init(mock_call_pool, sizeof(_mock_call_t), call_buffer, call_buffer+2048);
    my_test();
    return 0;
}