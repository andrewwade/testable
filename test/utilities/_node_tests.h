//
// Created by Andrew Wade on 7/2/18.
//

#ifndef TESTABLE_NODE_TEST_H
#define TESTABLE_NODE_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "clarity/testing.h"

TEST_GROUP(node_tests);

TEST(_node_initialize_allow_null_data);

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_NODE_TEST_H
