//
// Created by Andrew Wade on 2019-01-28.
//

#include "_query_tests.h"
#include "../source/query.h"


QUERY(EQUALS_INT_N, int, int) {
ASSERT_INT_EQ(input, subject);
}

QUERY(IS_NULL, void*, void) {
    ASSERT_PTR_NULL(subject);
}
QUERY(IS_NOT_NULL, void*, void) {
    ASSERT_PTR_NOT_NULL(subject);
}

TEST(integer_query_example) {
    int x = 4;

    EXPECT_THAT(x, EQUALS_INT_N(4));
    EXPECT_THAT(NULL, IS_NOT_NULL());
}

TEST_GROUP(query_tests) {
    TEST_CASE(integer_query_example);
}