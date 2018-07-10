//
// Created by Andrew Wade on 6/25/18.
//

#include "test/_node_test.h"

int main() {
    RUN_TEST_GROUP(node_test);
    RUN_TEST(_node_initialize_allow_null_data);
}