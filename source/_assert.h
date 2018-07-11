//
// Created by Andrew Wade on 6/29/18.
//

#ifndef TESTABLE_ASSERT_H
#define TESTABLE_ASSERT_H


#include "../include/portable.h"
#include <setjmp.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ARG(type, name) CHAR *name##_name, type name
#define LOC CHAR *file, UINT line
#define MSG CHAR *message, ...

#ifndef ASSERT_MSG_BUFFER_SIZE
#define ASSERT_MSG_BUFFER_SIZE 512
#endif

typedef struct fail_callback_t {
    void *user;
    void (*call)(void *user, int code, char *message);
} fail_callback_t;

jmp_buf *_assert_get_fail_point();

VOID _assert_push_fail_point(jmp_buf *point);

jmp_buf *_assert_pop_fail_point();

VOID _assert_add_fail_callback(fail_callback_t *callback);

VOID _assert_remove_fail_callback(fail_callback_t *callback);

/** CHAR **/
VOID _assert_char_equal(ARG(CHAR, expected), ARG(CHAR, actual), LOC, MSG);

VOID _assert_char_not_equal(ARG(CHAR, expected), ARG(CHAR, actual), LOC, MSG);

VOID _assert_char_less_than(ARG(CHAR, expected), ARG(CHAR, actual), LOC, MSG);

VOID _assert_char_greater_than(ARG(CHAR, expected), ARG(CHAR, actual), LOC, MSG);

VOID _assert_char_less_or_equal(ARG(CHAR, expected), ARG(CHAR, actual), LOC, MSG);

VOID _assert_char_greater_or_equal(ARG(CHAR, expected), ARG(CHAR, actual), LOC, MSG);

VOID _assert_char_in_range(ARG(CHAR, lower_limit), ARG(CHAR, upper_limit), ARG(CHAR, actual), LOC, MSG);

VOID _assert_char_in_array(ARG(CHAR *, _expected), ARG(ULONG, elen), ARG(CHAR *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_char_array_equal(ARG(CHAR *, _expected), ARG(CHAR *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_char_array_is_set(ARG(CHAR *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_char_array_is_subset(ARG(CHAR *, _expected), ARG(ULONG, elen), ARG(CHAR *, _actual), ARG(ULONG, alen), LOC, MSG);

VOID _assert_char_array_has_subset(ARG(CHAR *, _expected), ARG(ULONG, elen), ARG(CHAR *, _actual), ARG(ULONG, alen), LOC, MSG);

VOID _assert_char_array_is_string(ARG(CHAR *, _actual), ARG(ULONG, len), LOC, MSG);

/** UCHAR **/
VOID _assert_uchar_equal(ARG(UCHAR, expected), ARG(UCHAR, actual), LOC, MSG);

VOID _assert_uchar_not_equal(ARG(UCHAR, expected), ARG(UCHAR, actual), LOC, MSG);

VOID _assert_uchar_less_than(ARG(UCHAR, expected), ARG(UCHAR, actual), LOC, MSG);

VOID _assert_uchar_greater_than(ARG(UCHAR, expected), ARG(UCHAR, actual), LOC, MSG);

VOID _assert_uchar_less_or_equal(ARG(UCHAR, expected), ARG(UCHAR, actual), LOC, MSG);

VOID _assert_uchar_greater_or_equal(ARG(UCHAR, expected), ARG(UCHAR, actual), LOC, MSG);

VOID _assert_uchar_in_range(UCHAR low, ARG(UCHAR, high), ARG(UCHAR, actual), LOC, MSG);

VOID _assert_uchar_in_array(ARG(UCHAR *, _expected), ARG(ULONG, elen), ARG(UCHAR *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_uchar_array_equal(ARG(UCHAR *, _expected), ARG(UCHAR *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_uchar_array_is_set(ARG(UCHAR *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_uchar_array_is_subset(ARG(UCHAR *, _expected), ARG(ULONG, elen), ARG(UCHAR *, _actual), ARG(ULONG, alen), LOC, MSG);

VOID _assert_uchar_array_has_subset(ARG(UCHAR *, _expected), ARG(ULONG, elen), ARG(UCHAR *, _actual), ARG(ULONG, alen), LOC, MSG);

/** SHORT **/
VOID _assert_short_equal(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_short_not_equal(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_short_less_than(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_short_greater_than(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_short_less_or_equal(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_short_greater_or_equal(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_short_in_range(SHORT low, ARG(SHORT, high), ARG(SHORT, actual), LOC, MSG);

VOID _assert_short_in_array(ARG(SHORT *, _expected), ARG(ULONG, elen), ARG(SHORT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_short_array_equal(ARG(SHORT *, _expected), ARG(SHORT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_short_array_is_set(ARG(SHORT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_short_array_is_subset(ARG(SHORT *, _expected), ARG(ULONG, elen), ARG(SHORT *, _actual), ARG(ULONG, alen), LOC, MSG);

VOID _assert_short_array_has_subset(ARG(SHORT *, _expected), ARG(ULONG, elen), ARG(SHORT *, _actual), ARG(ULONG, alen), LOC, MSG);

/** USHORT **/
VOID _assert_ushort_equal(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_ushort_not_equal(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_ushort_less_than(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_ushort_greater_than(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_ushort_less_or_equal(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_ushort_greater_or_equal(ARG(SHORT, expected), ARG(SHORT, actual), LOC, MSG);

VOID _assert_ushort_in_range(SHORT low, ARG(SHORT, high), ARG(SHORT, actual), LOC, MSG);

VOID _assert_ushort_in_array(ARG(SHORT *, _expected), ARG(ULONG, elen), ARG(SHORT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_ushort_array_equal(ARG(SHORT *, _expected), ARG(SHORT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_ushort_array_is_set(ARG(SHORT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_ushort_array_is_subset(ARG(SHORT *, _expected), ARG(ULONG, elen), ARG(SHORT *, _actual), ARG(ULONG, alen), LOC, MSG);

VOID _assert_ushort_array_has_subset(ARG(SHORT *, _expected), ARG(ULONG, elen), ARG(SHORT *, _actual), ARG(ULONG, alen), LOC, MSG);

/** INT **/
VOID _assert_int_equal(ARG(INT, expected), ARG(INT, actual), LOC, MSG);

VOID _assert_int_not_equal(ARG(INT, expected), ARG(INT, actual), LOC, MSG);

VOID _assert_int_less_than(ARG(INT, expected), ARG(INT, actual), LOC, MSG);

VOID _assert_int_greater_than(ARG(INT, expected), ARG(INT, actual), LOC, MSG);

VOID _assert_int_less_or_equal(ARG(INT, expected), ARG(INT, actual), LOC, MSG);

VOID _assert_int_greater_or_equal(ARG(INT, expected), ARG(INT, actual), LOC, MSG);

VOID _assert_int_in_range(INT low, ARG(INT, high), ARG(INT, actual), LOC, MSG);

VOID _assert_int_in_array(ARG(INT *, _expected), ARG(ULONG, elen), ARG(INT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_int_array_equal(ARG(INT *, _expected), ARG(INT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_int_array_is_set(ARG(INT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_int_array_is_subset(ARG(INT *, _expected), ARG(ULONG, elen), ARG(INT *, _actual), ARG(ULONG, alen), LOC, MSG);

VOID _assert_int_array_has_subset(ARG(INT *, _expected), ARG(ULONG, elen), ARG(INT *, _actual), ARG(ULONG, alen), LOC, MSG);

/** UINT **/
VOID _assert_uint_equal(ARG(UINT, expected), ARG(UINT, actual), LOC, MSG);

VOID _assert_uint_not_equal(ARG(UINT, expected), ARG(UINT, actual), LOC, MSG);

VOID _assert_uint_less_than(ARG(UINT, expected), ARG(UINT, actual), LOC, MSG);

VOID _assert_uint_greater_than(ARG(UINT, expected), ARG(UINT, actual), LOC, MSG);

VOID _assert_uint_less_or_equal(ARG(UINT, expected), ARG(UINT, actual), LOC, MSG);

VOID _assert_uint_greater_or_equal(ARG(UINT, expected), ARG(UINT, actual), LOC, MSG);

VOID _assert_uint_in_range(UINT low, ARG(UINT, high), ARG(UINT, actual), LOC, MSG);

VOID _assert_uint_in_array(ARG(UINT *, _expected), ARG(ULONG, elen), ARG(UINT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_uint_array_equal(ARG(UINT *, _expected), ARG(UINT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_uint_array_is_set(ARG(UINT *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_uint_array_is_subset(ARG(UINT *, _expected), ARG(ULONG, elen), ARG(UINT *, _actual), ARG(ULONG, alen), LOC, MSG);

VOID _assert_uint_array_has_subset(ARG(UINT *, _expected), ARG(ULONG, elen), ARG(UINT *, _actual), ARG(ULONG, alen), LOC, MSG);

/** LONG **/
VOID _assert_long_equal(ARG(LONG, expected), ARG(LONG, actual), LOC, MSG);

VOID _assert_long_not_equal(ARG(LONG, expected), ARG(LONG, actual), LOC, MSG);

VOID _assert_long_less_than(ARG(LONG, expected), ARG(LONG, actual), LOC, MSG);

VOID _assert_long_greater_than(ARG(LONG, expected), ARG(LONG, actual), LOC, MSG);

VOID _assert_long_less_or_equal(ARG(LONG, expected), ARG(LONG, actual), LOC, MSG);

VOID _assert_long_greater_or_equal(ARG(LONG, expected), ARG(LONG, actual), LOC, MSG);

VOID _assert_long_in_range(LONG low, ARG(LONG, high), ARG(LONG, actual), LOC, MSG);

VOID _assert_long_in_array(ARG(LONG *, _expected), ARG(ULONG, elen), ARG(LONG *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_long_array_equal(ARG(LONG *, _expected), ARG(LONG *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_long_array_is_set(ARG(LONG *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_long_array_is_subset(ARG(LONG *, _expected), ARG(ULONG, elen), ARG(LONG *, _actual), ARG(ULONG, alen), LOC, MSG);

VOID _assert_long_array_has_subset(ARG(LONG *, _expected), ARG(ULONG, elen), ARG(LONG *, _actual), ARG(ULONG, alen), LOC, MSG);

/** ULONG **/
VOID _assert_ulong_equal(ARG(ULONG, expected), ARG(ULONG, actual), LOC, MSG);

VOID _assert_ulong_not_equal(ARG(ULONG, expected), ARG(ULONG, actual), LOC, MSG);

VOID _assert_ulong_less_than(ARG(ULONG, expected), ARG(ULONG, actual), LOC, MSG);

VOID _assert_ulong_greater_than(ARG(ULONG, expected), ARG(ULONG, actual), LOC, MSG);

VOID _assert_ulong_less_or_equal(ARG(ULONG, expected), ARG(ULONG, actual), LOC, MSG);

VOID _assert_ulong_greater_or_equal(ARG(ULONG, expected), ARG(ULONG, actual), LOC, MSG);

VOID _assert_ulong_in_range(ULONG low, ARG(ULONG, high), ARG(ULONG, actual), LOC, MSG);

VOID _assert_ulong_in_array(ARG(ULONG *, _expected), ARG(ULONG, elen), ARG(ULONG *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_ulong_array_equal(ARG(ULONG *, _expected), ARG(ULONG *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_ulong_array_is_set(ARG(ULONG *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_ulong_array_is_subset(ARG(ULONG *, _expected), ARG(ULONG, elen), ARG(ULONG *, _actual), ARG(ULONG, alen), LOC, MSG);

VOID _assert_ulong_array_has_subset(ARG(ULONG *, _expected), ARG(ULONG, elen), ARG(ULONG *, _actual), ARG(ULONG, alen), LOC, MSG);

/** STRING **/
VOID _assert_string_equal(ARG(CHAR *, _expected), ARG(CHAR *, _actual), LOC, MSG);

VOID _assert_string_not_equal(ARG(CHAR *, _expected), ARG(CHAR *, _actual), LOC, MSG);

/** PTR **/
VOID _assert_pointer_equal(ARG(VOID *, _expected), ARG(VOID *, _actual), LOC, MSG);

VOID _assert_pointer_not_equal(ARG(VOID *, _expected), ARG(VOID *, _actual), LOC, MSG);

/** MEMORY **/
VOID _assert_memory_equal(ARG(VOID *, _expected), ARG(VOID *, _actual), ARG(ULONG, len), LOC, MSG);

VOID _assert_memory_not_equal(ARG(VOID *, _expected), ARG(VOID *, _actual), ARG(ULONG, len), LOC, MSG);

#undef ARG
#undef LOC
#undef MSG

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_ASSERT_H
