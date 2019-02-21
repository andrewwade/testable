//
// Created by Andrew Wade on 2019-01-22.
//
#include "mocking/_mock_tests.h"
#include "utilities/_node_tests.h"
#include "utilities/_list_tests.h"
#include "utilities/_pool_tests.h"
#include "testing/_query_tests.h"
#include "runners.h"

int main() {
    CREATE_RUNNER(all_tests);
    RUNNER_ADD_GROUP(all_tests, node_tests);
//    RUNNER_ADD_GROUP(all_tests, list_tests);
    RUNNER_ADD_GROUP(all_tests, mock_tests);
    RUNNER_ADD_GROUP(all_tests, pool_tests);
    RUNNER_ADD_GROUP(all_tests, query_tests);
    RUNNER_RUN(all_tests);
}