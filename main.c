//
// Created by Andrew Wade on 6/25/18.
//

#include "test/_node_test.h"
#include "stdio.h"



#define MOCK_FUNCTION(ret, func, args...) \
ret mock_##func(##args);        \
struct {                        \
    int called;                 \
ret (*call)(##args);            \
} mock = {mock_##func};         \
ret func(##args) {              \
    mock.called++;              \
    return mock.call(a1,a2);    \
};                              \
ret mock_##func(##args)


//
//int main() {
//
//    RUN_TEST_GROUP(node_test);
//    RUN_TEST(_node_initialize_allow_null_data);
//}