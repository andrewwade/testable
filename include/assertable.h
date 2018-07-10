//
// Created by Andrew Wade on 6/29/18.
//

#ifndef TESTABLE_ASSERTABLE_H
#define TESTABLE_ASSERTABLE_H

#include "../source/_assert.h"
#include "portable.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ARG(name) #name, name
#define LOC __FILE__, __LINE__

#define _MSG_FMT_OR_DEFAULT(_1, fmt, ...) fmt
#define MSG_FMT(...) _MSG_FMT_OR_DEFAULT(,##__VA_ARGS__, NULL)
#define MSG_ARGS(fmt, ...) , ##__VA_ARGS__
#define MSG(...) MSG_FMT(__VA_ARGS__) MSG_ARGS(__VA_ARGS__)


/* generic comparators(not very descriptive) */
#if TEST_SUPPORT_VARIADIC_MACROS
#define ASSERT(condition, message...)
#define ASSERT_EQ(expected, actual, message...) ASSERT(actual == expected, message)
#define ASSERT_NE(expected, actual, message...) ASSERT(actual != expected, message)
#define ASSERT_GT(expected, actual, message...) ASSERT(actual > expected, message)
#define ASSERT_LT(expected, actual, message...) ASSERT(actual < expected, message)
#define ASSERT_GE(expected, actual, message...) ASSERT(actual >= expected, message)
#define ASSERT_LE(expected, actual, message...) ASSERT(actual <= expected, message)


/** CHAR */
/** assert that (actual == expected) */
#define ASSERT_CHAR_EQ(expected, actual, message...) \
_assert_char_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_CHAR_NE(expected, actual, message...) \
_assert_char_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_CHAR_GT(expected, actual), message...) \
_assert_char_greater_than(ARG((expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_CHAR_LT(expected, actual, message...) \
_assert_char_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_CHAR_GE(expected, actual, message...) \
_assert_char_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_CHAR_LE(expected, actual, message...) \
_assert_char_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_CHAR_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_char_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_CHAR_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_char_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_CHAR_IN_ARRAY(array, actual, len, message...) \
_assert_char_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_CHAR_NI_ARRAY(array, actual, len, message...) \
_assert_char_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_CHAR_ARRAY_EQ(expected, actual, len, message...) \
_assert_char_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_CHAR_ARRAY_NE(expected, actual, len, message...) \
_assert_char_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_CHAR_ARRAY_IS_SET(actual, len, message...) \
_assert_char_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_CHAR_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_char_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_CHAR_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_char_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == '\0') for some value i where (0 <= i < len) */
#define ASSERT_CHAR_ARRAY_IS_STRING(actual, len, message...) \
_assert_char_array_is_string(ARG(actual), ARG(len), LOC, MSG(message))

/** UCHAR **/
/* assert that (actual == expected) */
#define ASSERT_UCHAR_EQ(expected, actual, message...) \
_assert_uchar_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_UCHAR_NE(expected, actual, message...) \
_assert_uchar_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_UCHAR_GT(expected, actual, message...) \
_assert_uchar_greater_than(ARG((expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_UCHAR_LT(expected, actual, message...) \
_assert_uchar_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_UCHAR_GE(expected, actual, message...) \
_assert_uchar_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_UCHAR_LE(expected, actual, message...) \
_assert_uchar_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_UCHAR_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_uchar_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_UCHAR_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_uchar_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_UCHAR_IN_ARRAY(array, actual, len, message...) \
_assert_uchar_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_UCHAR_NI_ARRAY(array, actual, len, message...) \
_assert_uchar_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_UCHAR_ARRAY_EQ(expected, actual, len, message...) \
_assert_uchar_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_UCHAR_ARRAY_NE(expected, actual, len, message...) \
_assert_uchar_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_UCHAR_ARRAY_IS_SET(actual, len, message...) \
_assert_uchar_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_UCHAR_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_uchar_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_UCHAR_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_uchar_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))


/** SHORT **/
/* assert that (actual == expected) */
#define ASSERT_SHORT_EQ(expected, actual, message...) \
_assert_short_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_SHORT_NE(expected, actual, message...) \
_assert_short_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_SHORT_GT(expected, actual), message...) \
_assert_short_greater_than(ARG((expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_SHORT_LT(expected, actual, message...) \
_assert_short_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_SHORT_GE(expected, actual, message...) \
_assert_short_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_SHORT_LE(expected, actual, message...) \
_assert_short_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_SHORT_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_short_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_SHORT_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_short_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_SHORT_IN_ARRAY(array, actual, len, message...) \
_assert_short_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_SHORT_NI_ARRAY(array, actual, len, message...) \
_assert_short_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_SHORT_ARRAY_EQ(expected, actual, len, message...) \
_assert_short_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_SHORT_ARRAY_NE(expected, actual, len, message...) \
_assert_short_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_SHORT_ARRAY_IS_SET(actual, len, message...) \
_assert_short_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_SHORT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_short_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_SHORT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_short_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))


/** USHORT **/
/* assert that (actual == expected) */
#define ASSERT_USHORT_EQ(expected, actual, message...) \
_assert_ushort_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_USHORT_NE(expected, actual, message...) \
_assert_ushort_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_USHORT_GT(expected, actual), message...) \
_assert_ushort_greater_than(ARG((expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_USHORT_LT(expected, actual, message...) \
_assert_ushort_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_USHORT_GE(expected, actual, message...) \
_assert_ushort_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_USHORT_LE(expected, actual, message...) \
_assert_ushort_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_USHORT_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_ushort_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_USHORT_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_ushort_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_USHORT_IN_ARRAY(array, actual, len, message...) \
_assert_ushort_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_USHORT_NI_ARRAY(array, actual, len, message...) \
_assert_ushort_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_USHORT_ARRAY_EQ(expected, actual, len, message...) \
_assert_ushort_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_USHORT_ARRAY_NE(expected, actual, len, message...) \
_assert_ushort_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_USHORT_ARRAY_IS_SET(actual, len, message...) \
_assert_ushort_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_USHORT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_ushort_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_USHORT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_ushort_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))


/** INT **/
/* assert that (actual == expected) */
#define ASSERT_INT_EQ(expected, actual, message...) \
_assert_int_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_INT_NE(expected, actual, message...) \
_assert_int_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_INT_GT(expected, actual), message...) \
_assert_int_greater_than(ARG((expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_INT_LT(expected, actual, message...) \
_assert_int_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_INT_GE(expected, actual, message...) \
_assert_int_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_INT_LE(expected, actual, message...) \
_assert_int_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_INT_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_int_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_INT_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_int_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_INT_IN_ARRAY(array, actual, len, message...) \
_assert_int_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_INT_NI_ARRAY(array, actual, len, message...) \
_assert_int_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_INT_ARRAY_EQ(expected, actual, len, message...) \
_assert_int_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_INT_ARRAY_NE(expected, actual, len, message...) \
_assert_int_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_INT_ARRAY_IS_SET(actual, len, message...) \
_assert_int_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_INT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_int_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_INT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_int_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))


/** UINT **/
/* assert that (actual == expected) */
#define ASSERT_UINT_EQ(expected, actual, message...) \
_assert_uint_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_UINT_NE(expected, actual, message...) \
_assert_uint_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_UINT_GT(expected, actual, message...) \
_assert_uint_greater_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_UINT_LT(expected, actual, message...) \
_assert_uint_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_UINT_GE(expected, actual, message...) \
_assert_uint_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_UINT_LE(expected, actual, message...) \
_assert_uint_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_UINT_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_uint_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_UINT_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_uint_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_UINT_IN_ARRAY(array, actual, len, message...) \
_assert_uint_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_UINT_NI_ARRAY(array, actual, len, message...) \
_assert_uint_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_UINT_ARRAY_EQ(expected, actual, len, message...) \
_assert_uint_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_UINT_ARRAY_NE(expected, actual, len, message...) \
_assert_uint_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_UINT_ARRAY_IS_SET(actual, len, message...) \
_assert_uint_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_UINT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_uint_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_UINT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_uint_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/** LONG **/
/* assert that (actual == expected) */
#define ASSERT_LONG_EQ(expected, actual, message...) \
_assert_long_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_LONG_NE(expected, actual, message...) \
_assert_long_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_LONG_GT(expected, actual), message...) \
_assert_long_greater_than(ARG((expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_LONG_LT(expected, actual, message...) \
_assert_long_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_LONG_GE(expected, actual, message...) \
_assert_long_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_LONG_LE(expected, actual, message...) \
_assert_long_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_LONG_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_long_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_LONG_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_long_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_LONG_IN_ARRAY(array, actual, len, message...) \
_assert_long_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_LONG_NI_ARRAY(array, actual, len, message...) \
_assert_long_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_LONG_ARRAY_EQ(expected, actual, len, message...) \
_assert_long_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_LONG_ARRAY_NE(expected, actual, len, message...) \
_assert_long_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_LONG_ARRAY_IS_SET(actual, len, message...) \
_assert_long_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_LONG_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_long_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_LONG_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_long_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))


/** ULONG **/
/* assert that (actual == expected) */
#define ASSERT_ULONG_EQ(expected, actual, message...) \
_assert_ulong_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_ULONG_NE(expected, actual, message...) \
_assert_ulong_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_ULONG_GT(expected, actual), message...) \
_assert_ulong_greater_than(ARG((expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_ULONG_LT(expected, actual, message...) \
_assert_ulong_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_ULONG_GE(expected, actual, message...) \
_assert_ulong_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_ULONG_LE(expected, actual, message...) \
_assert_ulong_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_ULONG_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_ulong_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_ULONG_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_ulong_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_ULONG_IN_ARRAY(array, actual, len, message...) \
_assert_ulong_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_ULONG_NI_ARRAY(array, actual, len, message...) \
_assert_ulong_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_ULONG_ARRAY_EQ(expected, actual, len, message...) \
_assert_ulong_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_ULONG_ARRAY_NE(expected, actual, len, message...) \
_assert_ulong_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_ULONG_ARRAY_IS_SET(actual, len, message...) \
_assert_ulong_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_ULONG_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_ulong_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_ULONG_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_ulong_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))


/* test FLOAT values */
/** LONG **/
/* assert that (actual == expected) */
#define ASSERT_FLOAT_EQ(expected, actual, message...) \
_assert_float_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_FLOAT_NE(expected, actual, message...) \
_assert_float_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_FLOAT_GT(expected, actual), message...) \
_assert_float_greater_than(ARG((expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_FLOAT_LT(expected, actual, message...) \
_assert_float_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_FLOAT_GE(expected, actual, message...) \
_assert_float_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_FLOAT_LE(expected, actual, message...) \
_assert_float_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_FLOAT_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_float_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_FLOAT_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_float_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_FLOAT_IN_ARRAY(array, actual, len, message...) \
_assert_float_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_FLOAT_NI_ARRAY(array, actual, len, message...) \
_assert_float_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_FLOAT_ARRAY_EQ(expected, actual, len, message...) \
_assert_float_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_FLOAT_ARRAY_NE(expected, actual, len, message...) \
_assert_float_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_FLOAT_ARRAY_IS_SET(actual, len, message...) \
_assert_float_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_FLOAT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_float_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_FLOAT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_float_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))


/* test DOUBLE values */
/** DOUBLE **/
/* assert that (actual == expected) */
#define ASSERT_DOUBLE_EQ(expected, actual, message...) \
_assert_double_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual != expected) */
#define ASSERT_DOUBLE_NE(expected, actual, message...) \
_assert_double_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual > expected)*/
#define ASSERT_DOUBLE_GT(expected, actual), message...) \
_assert_double_greater_than(ARG((expected), ARG(actual), LOC, MSG(message))

/* assert that (actual < expected) */
#define ASSERT_DOUBLE_LT(expected, actual, message...) \
_assert_double_less_than(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (actual >= expected) */
#define ASSERT_DOUBLE_GE(expected, actual, message...) \
_assert_double_greater_or_equal(ARG(expected),ARG(actual), LOC, MSG(message))

/* assert that (actual <= expected) */
#define ASSERT_DOUBLE_LE(expected, actual, message...) \
_assert_double_less_or_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (lower_limit <= actual <= higher_limit) */
#define ASSERT_DOUBLE_IN_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_double_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (actual < lower_limit) or (actual > higher_limit) */
#define ASSERT_DOUBLE_NI_RANGE(lower_limit, higher_limit, actual, message...) \
_assert_double_not_in_range(ARG(lower_limit), ARG(higher_limit), ARG(actual), LOC, MSG(message))

/* assert that (array[i] == actual) for some value i where (0 <= i < len) */
#define ASSERT_DOUBLE_IN_ARRAY(array, actual, len, message...) \
_assert_double_in_array(ARG(array), ARG(actaul), ARG(len), LOC, MSG(message))

/* assert that (array[i] != actual) for all values of i where (0 <= i < len) */
#define ASSERT_DOUBLE_NI_ARRAY(array, actual, len, message...) \
_assert_double_not_in_array(ARG(array), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] == expected[i]) for all values of i where (0 <= i < len) */
#define ASSERT_DOUBLE_ARRAY_EQ(expected, actual, len, message...) \
_assert_double_array_equal(ARG(expected),ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != expected[i]) for some value i where (0 <= i < len) */
#define ASSERT_DOUBLE_ARRAY_NE(expected, actual, len, message...) \
_assert_double_array_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (actual[i] != actual[j]) for all values of i and j where (0 <= i < len) and (0 <= j < len) and (i != j) */
#define ASSERT_DOUBLE_ARRAY_IS_SET(actual, len, message...) \
_assert_double_array_is_set(ARG(actual), ARG(len), LOC, MSG(message))

/* assert that (expected[i] == actual[j]) for all values of i where (0 <= i < expected_length) and some value j where (0 <= j < actual_length) */
#define ASSERT_DOUBLE_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_double_array_has_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))

/* assert that (actual[i] == expected[j]) for all values of i where (0 <= i < actual_length) and some value j where (0 <= j < expected_length) */
#define ASSERT_DOUBLE_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length, message...) \
_assert_double_array_is_subset(ARG(expected), ARG(expected_length), ARG(actual), ARG(actual_length), LOC, MSG(message))


/** POINTER **/
/* assert that (expected == actual) */
#define ASSERT_PTR_EQ(expected, actual, message...) \
_assert_pointer_equal(ARG(expected), ARG(actual), LOC, MSG(message))

#define ASSERT_PTR_NE(expected, actual, message...) \
_assert_pointer_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/** STRING **/
/* assert that (expected[i] == actual[i]) for all values of i where (0 <= i < max(strlen(expected), strlen(actual))) */
#define ASSERT_STRING_EQ(expected, actual, message...) \
_assert_string_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/* assert that (expected[i] != actual[i]) for some value i where (0 <= i < strlen(expected)) */
#define ASSERT_STRING_NE(expected, actual, message...) \
_assert_string_not_equal(ARG(expected), ARG(actual), LOC, MSG(message))

/** MEMORY **/
/* assert that ((CHAR*)expected[i] == (CHAR*)actual[i]) for all values of i where (0 <= i < len) */
#define ASSERT_MEMORY_EQ(expected, actual, len, message...) \
_assert_memory_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

/* assert that ((CHAR*)expected[i] != (CHAR *)actual[i]) for some value of i where (0 <= i < len) */
#define ASSERT_MEMORY_NEQ(expected, actual, len, message...) \
_assert_memory_not_equal(ARG(expected), ARG(actual), ARG(len), LOC, MSG(message))

#else /* ASSERT_VARIADIC_MACROS_SUPPORTED == 0 */
#define TEST(condition, ...)

/* test CHAR values */
#define ASSERT_CHAR_EQ_MESSAGE(expected, actual, message)
#define ASSERT_CHAR_EQ(expected, actual)     _testable_char_equal(expected, actual, __VA__ARGS__)
#define ASSERT_CHAR_NE_MESSAGE(expected, actual, message)
#define ASSERT_CHAR_NE(expected, actual)
#define ASSERT_CHAR_GT_MESSAGE(expected, actual, message)
#define ASSERT_CHAR_GT(expected, actual)
#define ASSERT_CHAR_LT_MESSAGE(expected, actual, message)
#define ASSERT_CHAR_LT(expected, actual)
#define ASSERT_CHAR_GE_MESSAGE(expected, actual, message)
#define ASSERT_CHAR_GE(expected, actual)
#define ASSERT_CHAR_LE_MESSAGE(expected, actual, message)
#define ASSERT_CHAR_LE(expected, actual)
#define ASSERT_CHAR_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_CHAR_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_CHAR_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_CHAR_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_CHAR_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_CHAR_IN_ARRAY(array, actual, len)
#define ASSERT_CHAR_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_CHAR_NI_ARRAY(array, actual, len)
#define ASSERT_CHAR_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_CHAR_ARRAY_EQ(expected, actual, len)
#define ASSERT_CHAR_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_CHAR_ARRAY_NE(expected, actual, len)
#define ASSERT_CHAR_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_CHAR_ARRAY_IS_SET(actual, len)
#define ASSERT_CHAR_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_CHAR_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_CHAR_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_CHAR_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_CHAR_ARRAY_IS_STRING_MESSAGE(actual, len, message)
#define ASSERT_CHAR_ARRAY_IS_STRING(actual, len)

/* test UCHAR values */
#define ASSERT_UCHAR_EQ_MESSAGE(expected, actual, message)
#define ASSERT_UCHAR_EQ(expected, actual)
#define ASSERT_UCHAR_NEQ__MESSAGE(expected, actual, message)
#define ASSERT_UCHAR_NEQ_(expected, actual)
#define ASSERT_UCHAR_GT_MESSAGE(expected, actual, message)
#define ASSERT_UCHAR_GT(expected, actual)
#define ASSERT_UCHAR_LT_MESSAGE(expected, actual, message)
#define ASSERT_UCHAR_LT(expected, actual)
#define ASSERT_UCHAR_GE_MESSAGE(expected, actual, message)
#define ASSERT_UCHAR_GE(expected, actual)
#define ASSERT_UCHAR_LE_MESSAGE(expected, actual, message)
#define ASSERT_UCHAR_LE(expected, actual)
#define ASSERT_UCHAR_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_UCHAR_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_UCHAR_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_UCHAR_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_UCHAR_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_UCHAR_IN_ARRAY(array, actual, len)
#define ASSERT_UCHAR_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_UCHAR_NI_ARRAY(array, actual, len)
#define ASSERT_UCHAR_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_UCHAR_ARRAY_EQ(expected, actual, len)
#define ASSERT_UCHAR_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_UCHAR_ARRAY_NE(expected, actual, len)
#define ASSERT_UCHAR_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_UCHAR_ARRAY_IS_SET(actual, len)
#define ASSERT_UCHAR_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_UCHAR_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_UCHAR_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_UCHAR_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)

/* test SHORT values */
#define ASSERT_SHORT_EQ_MESSAGE(expected, actual, message)
#define ASSERT_SHORT_EQ(expected, actual)
#define ASSERT_SHORT_NEQ__MESSAGE(expected, actual, message)
#define ASSERT_SHORT_NEQ_(expected, actual)
#define ASSERT_SHORT_GT_MESSAGE(expected, actual, message)
#define ASSERT_SHORT_GT(expected, actual)
#define ASSERT_SHORT_LT_MESSAGE(expected, actual, message)
#define ASSERT_SHORT_LT(expected, actual)
#define ASSERT_SHORT_GE_MESSAGE(expected, actual, message)
#define ASSERT_SHORT_GE(expected, actual)
#define ASSERT_SHORT_LE_MESSAGE(expected, actual, message)
#define ASSERT_SHORT_LE(expected, actual)
#define ASSERT_SHORT_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_SHORT_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_SHORT_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_SHORT_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_SHORT_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_SHORT_IN_ARRAY(array, actual, len)
#define ASSERT_SHORT_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_SHORT_NI_ARRAY(array, actual, len)
#define ASSERT_SHORT_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_SHORT_ARRAY_EQ(expected, actual, len)
#define ASSERT_SHORT_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_SHORT_ARRAY_NE(expected, actual, len)
#define ASSERT_SHORT_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_SHORT_ARRAY_IS_SET(actual, len)
#define ASSERT_SHORT_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_SHORT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_SHORT_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_SHORT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)

/* test USHORT values */
#define ASSERT_USHORT_EQ_MESSAGE(expected, actual, message)
#define ASSERT_USHORT_EQ(expected, actual)
#define ASSERT_USHORT_NEQ__MESSAGE(expected, actual, message)
#define ASSERT_USHORT_NEQ_(expected, actual)
#define ASSERT_USHORT_GT_MESSAGE(expected, actual, message)
#define ASSERT_USHORT_GT(expected, actual)
#define ASSERT_USHORT_LT_MESSAGE(expected, actual, message)
#define ASSERT_USHORT_LT(expected, actual)
#define ASSERT_USHORT_GE_MESSAGE(expected, actual, message)
#define ASSERT_USHORT_GE(expected, actual)
#define ASSERT_USHORT_LE_MESSAGE(expected, actual, message)
#define ASSERT_USHORT_LE(expected, actual)
#define ASSERT_USHORT_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_USHORT_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_USHORT_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_USHORT_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_USHORT_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_USHORT_IN_ARRAY(array, actual, len)
#define ASSERT_USHORT_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_USHORT_NI_ARRAY(array, actual, len)
#define ASSERT_USHORT_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_USHORT_ARRAY_EQ(expected, actual, len)
#define ASSERT_USHORT_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_USHORT_ARRAY_NE(expected, actual, len)
#define ASSERT_USHORT_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_USHORT_ARRAY_IS_SET(actual, len)
#define ASSERT_USHORT_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_USHORT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_USHORT_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_USHORT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)

/* test INT values */
#define ASSERT_INT_EQ_MESSAGE(expected, actual, message)
#define ASSERT_INT_EQ(expected, actual)
#define ASSERT_INT_NEQ__MESSAGE(expected, actual, message)
#define ASSERT_INT_NEQ_(expected, actual)
#define ASSERT_INT_GT_MESSAGE(expected, actual, message)
#define ASSERT_INT_GT(expected, actual)
#define ASSERT_INT_LT_MESSAGE(expected, actual, message)
#define ASSERT_INT_LT(expected, actual)
#define ASSERT_INT_GE_MESSAGE(expected, actual, message)
#define ASSERT_INT_GE(expected, actual)
#define ASSERT_INT_LE_MESSAGE(expected, actual, message)
#define ASSERT_INT_LE(expected, actual)
#define ASSERT_INT_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_INT_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_INT_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_INT_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_INT_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_INT_IN_ARRAY(array, actual, len)
#define ASSERT_INT_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_INT_NI_ARRAY(array, actual, len)
#define ASSERT_INT_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_INT_ARRAY_EQ(expected, actual, len)
#define ASSERT_INT_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_INT_ARRAY_NE(expected, actual, len)
#define ASSERT_INT_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_INT_ARRAY_IS_SET(actual, len)
#define ASSERT_INT_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_INT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_INT_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_INT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)

/* test UINT values */
#define ASSERT_UINT_EQ_MESSAGE(expected, actual, message)
#define ASSERT_UINT_EQ(expected, actual)
#define ASSERT_UINT_NEQ__MESSAGE(expected, actual, message)
#define ASSERT_UINT_NEQ_(expected, actual)
#define ASSERT_UINT_GT_MESSAGE(expected, actual, message)
#define ASSERT_UINT_GT(expected, actual)
#define ASSERT_UINT_LT_MESSAGE(expected, actual, message)
#define ASSERT_UINT_LT(expected, actual)
#define ASSERT_UINT_GE_MESSAGE(expected, actual, message)
#define ASSERT_UINT_GE(expected, actual)
#define ASSERT_UINT_LE_MESSAGE(expected, actual, message)
#define ASSERT_UINT_LE(expected, actual)
#define ASSERT_UINT_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_UINT_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_UINT_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_UINT_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_UINT_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_UINT_IN_ARRAY(array, actual, len)
#define ASSERT_UINT_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_UINT_NI_ARRAY(array, actual, len)
#define ASSERT_UINT_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_UINT_ARRAY_EQ(expected, actual, len)
#define ASSERT_UINT_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_UINT_ARRAY_NE(expected, actual, len)
#define ASSERT_UINT_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_UINT_ARRAY_IS_SET(actual, len)
#define ASSERT_UINT_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_UINT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_UINT_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_UINT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)

/* test LONG values */
#define ASSERT_LONG_EQ_MESSAGE(expected, actual, message)
#define ASSERT_LONG_EQ(expected, actual)
#define ASSERT_LONG_NEQ__MESSAGE(expected, actual, message)
#define ASSERT_LONG_NEQ_(expected, actual)
#define ASSERT_LONG_GT_MESSAGE(expected, actual, message)
#define ASSERT_LONG_GT(expected, actual)
#define ASSERT_LONG_LT_MESSAGE(expected, actual, message)
#define ASSERT_LONG_LT(expected, actual)
#define ASSERT_LONG_GE_MESSAGE(expected, actual, message)
#define ASSERT_LONG_GE(expected, actual)
#define ASSERT_LONG_LE_MESSAGE(expected, actual, message)
#define ASSERT_LONG_LE(expected, actual)
#define ASSERT_LONG_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_LONG_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_LONG_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_LONG_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_LONG_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_LONG_IN_ARRAY(array, actual, len)
#define ASSERT_LONG_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_LONG_NI_ARRAY(array, actual, len)
#define ASSERT_LONG_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_LONG_ARRAY_EQ(expected, actual, len)
#define ASSERT_LONG_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_LONG_ARRAY_NE(expected, actual, len)
#define ASSERT_LONG_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_LONG_ARRAY_IS_SET(actual, len)
#define ASSERT_LONG_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_LONG_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_LONG_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_LONG_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)

/* test ULONG values */
#define ASSERT_ULONG_EQ_MESSAGE(expected, actual, message)
#define ASSERT_ULONG_EQ(expected, actual)
#define ASSERT_ULONG_NEQ__MESSAGE(expected, actual, message)
#define ASSERT_ULONG_NEQ_(expected, actual)
#define ASSERT_ULONG_GT_MESSAGE(expected, actual, message)
#define ASSERT_ULONG_GT(expected, actual)
#define ASSERT_ULONG_LT_MESSAGE(expected, actual, message)
#define ASSERT_ULONG_LT(expected, actual)
#define ASSERT_ULONG_GE_MESSAGE(expected, actual, message)
#define ASSERT_ULONG_GE(expected, actual)
#define ASSERT_ULONG_LE_MESSAGE(expected, actual, message)
#define ASSERT_ULONG_LE(expected, actual)
#define ASSERT_ULONG_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_ULONG_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_ULONG_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_ULONG_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_ULONG_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_ULONG_IN_ARRAY(array, actual, len)
#define ASSERT_ULONG_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_ULONG_NI_ARRAY(array, actual, len)
#define ASSERT_ULONG_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_ULONG_ARRAY_EQ(expected, actual, len)
#define ASSERT_ULONG_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_ULONG_ARRAY_NE(expected, actual, len)
#define ASSERT_ULONG_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_ULONG_ARRAY_IS_SET(actual, len)
#define ASSERT_ULONG_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_ULONG_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_ULONG_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_ULONG_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)

/* test FLOAT values */
#define ASSERT_FLOAT_EQ_MESSAGE(expected, actual, message)
#define ASSERT_FLOAT_EQ(expected, actual)
#define ASSERT_FLOAT_NEQ__MESSAGE(expected, actual, message)
#define ASSERT_FLOAT_NEQ_(expected, actual)
#define ASSERT_FLOAT_GT_MESSAGE(expected, actual, message)
#define ASSERT_FLOAT_GT(expected, actual)
#define ASSERT_FLOAT_LT_MESSAGE(expected, actual, message)
#define ASSERT_FLOAT_LT(expected, actual)
#define ASSERT_FLOAT_GE_MESSAGE(expected, actual, message)
#define ASSERT_FLOAT_GE(expected, actual)
#define ASSERT_FLOAT_LE_MESSAGE(expected, actual, message)
#define ASSERT_FLOAT_LE(expected, actual)
#define ASSERT_FLOAT_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_FLOAT_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_FLOAT_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_FLOAT_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_FLOAT_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_FLOAT_IN_ARRAY(array, actual, len)
#define ASSERT_FLOAT_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_FLOAT_NI_ARRAY(array, actual, len)
#define ASSERT_FLOAT_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_FLOAT_ARRAY_EQ(expected, actual, len)
#define ASSERT_FLOAT_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_FLOAT_ARRAY_NE(expected, actual, len)
#define ASSERT_FLOAT_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_FLOAT_ARRAY_IS_SET(actual, len)
#define ASSERT_FLOAT_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_FLOAT_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_FLOAT_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_FLOAT_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)

/* test DOUBLE values */
#define ASSERT_DOUBLE_EQ_MESSAGE(expected, actual, message)
#define ASSERT_DOUBLE_EQ(expected, actual)
#define ASSERT_DOUBLE_NEQ__MESSAGE(expected, actual, message)
#define ASSERT_DOUBLE_NEQ_(expected, actual)
#define ASSERT_DOUBLE_GT_MESSAGE(expected, actual, message)
#define ASSERT_DOUBLE_GT(expected, actual)
#define ASSERT_DOUBLE_LT_MESSAGE(expected, actual, message)
#define ASSERT_DOUBLE_LT(expected, actual)
#define ASSERT_DOUBLE_GE_MESSAGE(expected, actual, message)
#define ASSERT_DOUBLE_GE(expected, actual)
#define ASSERT_DOUBLE_LE_MESSAGE(expected, actual, message)
#define ASSERT_DOUBLE_LE(expected, actual)
#define ASSERT_DOUBLE_IN_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_DOUBLE_IN_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_DOUBLE_NI_RANGE_MESSAGE(lower_limit, higher_limit, actual, message)
#define ASSERT_DOUBLE_NI_RANGE(lower_limit, higher_limit, actual)
#define ASSERT_DOUBLE_IN_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_DOUBLE_IN_ARRAY(array, actual, len)
#define ASSERT_DOUBLE_NI_ARRAY_MESSAGE(array, actual, len, message)
#define ASSERT_DOUBLE_NI_ARRAY(array, actual, len)
#define ASSERT_DOUBLE_ARRAY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_DOUBLE_ARRAY_EQ(expected, actual, len)
#define ASSERT_DOUBLE_ARRAY_NEMESSAGE(expected, actual, len, message)
#define ASSERT_DOUBLE_ARRAY_NE(expected, actual, len)
#define ASSERT_DOUBLE_ARRAY_IS_SET_MESSAGE(actual, len, message)
#define ASSERT_DOUBLE_ARRAY_IS_SET(actual, len)
#define ASSERT_DOUBLE_ARRAY_HAS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_DOUBLE_ARRAY_HAS_SUBSET(expected, expected_length, actual, actual_length)
#define ASSERT_DOUBLE_ARRAY_IS_SUBSET_MESSAGE(expected, expected_length, actual, actual_length, message)
#define ASSERT_DOUBLE_ARRAY_IS_SUBSET(expected, expected_length, actual, actual_length)

/* test string values */
#define ASSERT_PTR_EQ_MESSAGE(expected, actual, message)
#define ASSERT_PTR_EQ(expected, actual)
#define ASSERT_STRING_EQ_MESSAGE(expected, actual, message)
#define ASSERT_STRING_EQ(expected, actual)
#define ASSERT_STRING_NEQ_MESSAGE(expected, actual, message)
#define ASSERT_STRING_NEQ(expected, actual)

/* test memory values */
#define ASSERT_MEMORY_EQ_MESSAGE(expected, actual, len, message)
#define ASSERT_MEMORY_EQ(expected, actual, len)
#define ASSERT_MEMORY_NEQ_MESSAGE(expected, actual, len, message)
#define ASSERT_MEMORY_NEQ(expected, actual, len)
#endif


#ifdef __cplusplus
};
#endif

#endif //TESTABLE_ASSERT_H
