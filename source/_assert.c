#include "../include/testing.h"
#include <stdio.h>
#include <stdarg.h>

static void (*fail_callback)(_assert_t *) = NULL;

#define ASSERT_PTR_EQ_FAILED 1

#define ASSERT_FAILED(a) if(fail_callback){fail_callback(a);}


static void vlog_failure(CHAR *failure, CHAR *expected_name, CHAR expected, CHAR *actual_name, CHAR actual, CHAR *file, UINT line, CHAR *msg, va_list msg_args) {
    printf("%s(%d):\nTest Failure: %s\n\tExpected: %s: %d('%c')\n\t  Actual: %s: %d('%c')\n",
           file, line, failure, expected_name, expected, expected, actual_name, actual, actual);
    if (msg) {
        printf("     Message: ");
        vprintf(msg, msg_args);
    }
    printf("\n");
}

VOID _assert_set_fail_callback(void (*callback)(int coZ *)) {
    fail_callback = callback;
}

VOID _assert_char_equal(CHAR *expected_name, CHAR expected, CHAR *actual_name, CHAR actual, CHAR *file, UINT line, char *message, ...) {
    if (expected != actual) {
        va_list args;
        va_start(args, message);
        vlog_failure("Chars Not Equal!", expected_name, expected, actual_name, actual, file, line, message, args);
        va_end(args);
        if (fail_callback) {
            fail_callback(NULL);
        }
    }
}

VOID _assert_char_not_equal(CHAR *expected_name, CHAR expected, CHAR *actual_name, CHAR actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        _assert_t a = {};
        va_list   args;
        va_start(args, message);
        vlog_failure("Chars Equal!", expected_name, expected, actual_name, actual, file, line, message, args);
        va_end(args);
        ASSERT_FAILED(&a);
    }
}

VOID _assert_pointer_equal(CHAR *expected_name, VOID *expected, CHAR *actual_name, VOID *actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected != actual) {
        int       msglen = 0;
        _assert_t a      = {ASSERT_PTR_EQ_FAILED};
        msglen = snprintf(a.message, ASSERT_MSG_BUFFER_SIZE,
                          "%s(%d):\n"
                          "Test Failure: Pointers not equal when they should be.\n"
                          "    Expected: %16s: %p\n"
                          "      Actual: %16s: %p",
                          file, line, expected_name, expected, actual_name, actual);
        if (message) {
            va_list args;
            va_start(args, message);
            msglen += snprintf(&a.message[msglen], ASSERT_MSG_BUFFER_SIZE - msglen, "\n     Message: ");
            msglen += vsnprintf(&a.message[msglen], ASSERT_MSG_BUFFER_SIZE - msglen, message, args);
            va_end(args);
        }
        sprintf(&a.message[msglen], ASSERT_MSG_BUFFER_SIZE - msglen, "\n");
        ASSERT_FAILED(&a);
    }
}

VOID _assert_pointer_not_equal(CHAR *expected_name, VOID *expected, CHAR *actual_name, VOID *actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        int       msglen = 0;
        _assert_t a      = {2};
        msglen = snprintf(a.message, ASSERT_MSG_BUFFER_SIZE,
                         "%s(%d):\n"
                         "Test Failure: Pointers are equal when they shouldn't be.\n"
                         "    Expected: %16s: %p\n"
                         "      Actual: %16s: %p",
                         file, line, expected_name, expected, actual_name, actual);
        if (message) {
            va_list args;
            va_start(args, message);
            msglen += snprintf(&a.message[msglen], ASSERT_MSG_BUFFER_SIZE - msglen, "\n     Message: ");
            msglen += vsnprintf(&a.message[msglen], ASSERT_MSG_BUFFER_SIZE - msglen, message, args);
            va_end(args);
        }
        printf("\n");
        ASSERT_FAILED(&a);
    }
}

VOID _assert_uint_greater_than(CHAR *expected_name, UINT expected, CHAR *actual_name, UINT actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        _assert_t a;
        printf("%s(%d):\nTest Failure: Uint is not greater than expected.\n\tExpected: %16s: %d\n\t  Actual: %16s: %d\n",
               file, line, expected_name, expected, actual_name, actual);
        if (message) {
            va_list args;
            va_start(args, message);
            printf("     Message: ");
            vprintf(message, args);
            va_end(args);
        }
        printf("\n");
        ASSERT_FAILED(&a);
    }
}

VOID _assert_uint_not_equal(CHAR *expected_name, UINT expected, CHAR *actual_name, UINT actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        printf("%s(%d):\nTest Failure: UINT not expected to be equal.\n\tExpected: %16s: %d\n\t  Actual: %16s: %d\n",
               file, line, expected_name, expected, actual_name, actual);
        if (message) {
            va_list args;
            va_start(args, message);
            printf("     Message: ");
            vprintf(message, args);
            va_end(args);
        }
        printf("\n");
        ASSERT_FAILED(NULL);
    }
}