//
// Created by Andrew Wade on 2019-01-22.
//
#include "_mock_tests.h"
#include "_node_tests.h"

int main() {
    RUN_TEST_GROUP(node_tests);
    RUN_TEST_GROUP(mock_tests);
}