//
// Created by Andrew Wade on 2019-01-25.
//

#include "_pool_tests.h"
#include "../../source/utilities/_pool.h"

struct int_eval_t {
    int  expected;
    void (*eval)(struct int_eval_t *self, int actual);
} test_eval;


void int_equal(struct int_eval_t *self, int actual) {
    ASSERT(self->expected == actual);
}

struct int_eval_t *new_int_eval(int expected) {
    test_eval.expected = expected;
    test_eval.eval = int_equal;
    return &test_eval;
}


#define EXPECT_THAT(var, op) (op)->eval((op), (var))

#define EQUALS_INT(in) new_int_eval(in)

TEST(pool_should_initialize) {
    _pool_t pool;
    char    buffer[14];
    _pool_init(&pool, 14, buffer, buffer + 14);
    ASSERT_PTR_EQ(pool.search, pool.start);
    ASSERT_PTR_EQ(pool.start, buffer);
    ASSERT_PTR_EQ(pool.end, &buffer[14]);
    ASSERT_INT_EQ(pool.alignment, 14);
    EXPECT_THAT((int)pool.alignment, EQUALS_INT(14));
}

TEST(pool_should_fail) {
    _pool_t pool;
    char    buffer[14];
    EXPECT_ASSERT_FAILURE(
        _pool_init(&pool, 0, buffer, buffer + 14),
        "Shouldn't allow 0 alignment"
    );
}

TEST_GROUP(pool_tests) {
    TEST_CASE(pool_should_initialize);
    TEST_CASE(pool_should_fail);
}