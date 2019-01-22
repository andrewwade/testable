#include "testable.h"
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include "_assert.h"

#define STRING_NAME(name) #name
#define TO_STRING(x) STRING_NAME(x)

#define ASSERT_FAILED(code, msg)           \
assert_fail_callback(code, msg);           \
longjmp(*(_assert_get_fail_point()), code)

static _node_t *fail_jump_stack          = NULL;
static _node_t *fail_callback_queue      = NULL;
static INT     fail_callback_queue_count = 0;

static char null[] = "NULL";


static VOID assert_fail_callback(int code, char *message) {
    fail_callback_t *callback;
    if (fail_callback_queue != NULL) {
        _node_t *node = fail_callback_queue;
        do {
            callback = node->data;
            callback->call(callback->user, code, message);
        } while (node != fail_callback_queue);
    }
}

static void append_location(char *buf, char *file, unsigned int line) {
    unsigned int max_length = ASSERT_MSG_BUFFER_SIZE;
    /* go to end of string */
    while (*buf != '\0') {
        max_length--;
        buf++;
    }
    snprintf(buf, max_length, "     Location: %s(%d):\n", file, line);
}

static void append_failure(char *buf, char *fmt, ...) {
    va_list      args;
    int          write_length = 0;
    unsigned int max_length   = ASSERT_MSG_BUFFER_SIZE;
    /* go to end of string */
    while (*buf != '\0') {
        max_length--;
        buf++;
    }

    write_length = snprintf(buf, max_length, "Assert Failed: ");
    buf += write_length;
    max_length -= write_length;
    va_start(args, fmt);
    write_length = vsnprintf(buf, max_length, fmt, args);
    buf += write_length;
    max_length -= write_length;
    snprintf(buf, max_length, "\n");
    va_end(args);
}

static void append_argument(char *buf, char *arg, char *arg_name, char *fmt, ...) {
    va_list      args;
    unsigned int write_length = 0;
    unsigned int max_length   = ASSERT_MSG_BUFFER_SIZE;

    /* go to end of string */
    while (*buf != '\0') {
        max_length--;
        buf++;
    }

    /* if argument is NULL */
    if (!strcmp(TO_STRING(NULL), arg_name)) {
        /* change argument name to "NULL" instead of "((void*)0)" */
        arg_name = null;
    }

    write_length = snprintf(buf, max_length, "%13s: %16s: ", arg, arg_name);
    buf += write_length;
    max_length -= write_length;

    va_start(args, fmt);
    write_length = vsnprintf(buf, max_length, fmt, args);
    buf += write_length;
    max_length -= write_length;
    snprintf(buf, max_length, "\n");
    va_end(args);
}

static void append_message(char *buf, char *fmt, ...) {
    unsigned int max_length = ASSERT_MSG_BUFFER_SIZE;
    /* go to end of string */
    while (*buf != '\0') {
        max_length--;
        buf++;
    }
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, max_length, fmt, args);
    va_end(args);
}

static void append_vmessage(char *buf, char *fmt, va_list args) {
    unsigned int write_length = 0;
    unsigned int max_length   = ASSERT_MSG_BUFFER_SIZE;

    /* check for null pointers */
    if (buf == NULL || fmt == NULL) {
        return;
    }

    /* go to end of string */
    while (*buf != '\0') {
        max_length--;
        buf++;
    }

    write_length = snprintf(buf, max_length, "%13s: ", "Message");
    buf += write_length;
    max_length -= write_length;

    write_length = vsnprintf(buf, max_length, fmt, args);
    buf += write_length;
    max_length -= write_length;
    snprintf(buf, max_length, "\n");
}


VOID _assert_push_fail_point(jmp_buf *jump) {
    _node_t *node = _node_allocate();
    _node_initialize(node, jump);
    if (fail_jump_stack == NULL) {
        fail_jump_stack = node;
    } else {
        _node_insert(fail_jump_stack, node);
    }
}

jmp_buf *_assert_pop_fail_point() {
    _node_t *pop_node;
    jmp_buf *pop_point;

    if (fail_jump_stack == NULL) {
        return NULL;
    } else {
        pop_node  = _node_last(fail_jump_stack);
        pop_point = _node_data(pop_node);
        _node_remove(pop_node);
        _node_release(pop_node);
        return pop_point;
    }
}

jmp_buf *_assert_get_fail_point() {
    if (fail_jump_stack == NULL) {
        return NULL;
    } else {
        return _node_last(fail_jump_stack)->data;
    }
}

VOID _assert_add_fail_callback(fail_callback_t *callback) {
    _node_t *node = _node_allocate();
    _node_initialize(node, callback);
    if (fail_callback_queue == NULL) {
        fail_callback_queue = node;
    } else {
        _node_insert(fail_callback_queue, node);
    }
    fail_callback_queue_count++;
}

VOID _assert_remove_fail_callback(fail_callback_t *callback) {
    _node_t *node = fail_callback_queue;
    do {
        if (node->data == callback) {
            _node_remove(node);
            _node_release(node);
            fail_callback_queue_count--;
            break;
        }
        node = _node_next(node);
    } while (node != fail_callback_queue);
    if (fail_callback_queue_count == 0) {
        fail_callback_queue = NULL;
    }

}

VOID _assert_true(CHAR *explanation, BOOLEAN condition, CHAR *file, UINT line, char *message, ...) {
    if(!condition) {
        va_list args;
        char buf[ASSERT_MSG_BUFFER_SIZE] = {0};
        va_start(args, message);
        append_location(buf, file, line);
        append_failure(buf, "Condition should be true!");
        append_argument(buf, "Condition", explanation, "%s", "false");
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_false(CHAR *explanation, BOOLEAN condition, CHAR *file, UINT line, char *message, ...) {
    if(condition) {
        va_list args;
        char buf[ASSERT_MSG_BUFFER_SIZE] = {0};
        va_start(args, message);
        append_location(buf, file, line);
        append_failure(buf, "Condition should be true!");
        append_argument(buf, "Condition", explanation, "%s", "true");
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_char_equal(CHAR *expected_name, CHAR expected, CHAR *actual_name, CHAR actual, CHAR *file, UINT line, char *message, ...) {
    if (expected != actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};
        va_start(args, message);
        append_location(buf, file, line);
        append_failure(buf, "Chars should be equal!");
        append_argument(buf, "Expected", expected_name, "%c", expected);
        append_argument(buf, "Actual", actual_name, "%c", actual);
        append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_char_not_equal(CHAR *expected_name, CHAR expected, CHAR *actual_name, CHAR actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);
        append_location(buf, file, line);
        append_failure(buf, "Chars should not be equal!");
        append_argument(buf, "Expected", expected_name, "%c", expected);
        append_argument(buf, "Actual", actual_name, "%c", actual);
        append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_pointer_equal(CHAR *expected_name, VOID *expected, CHAR *actual_name, VOID *actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected != actual) {
        va_list args;
        int     msglen                      = 0;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};
        va_start(args, message);
        append_location(buf, file, line);
        append_failure(buf, "Pointers should be equal");
        append_argument(buf, "Expected", expected_name, "%p", expected);
        append_argument(buf, "Actual", actual_name, "%p", actual);
        append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_pointer_not_equal(CHAR *expected_name, VOID *expected, CHAR *actual_name, VOID *actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);
        append_location(buf, file, line);
        append_failure(buf, "Pointers should not be equal.");
        append_argument(buf, "Expected", expected_name, "%p", expected);
        append_argument(buf, "Actual", actual_name, "%p", actual);
        append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_uint_greater_than(CHAR *expected_name, UINT expected, CHAR *actual_name, UINT actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);
        append_location(buf, file, line);
        append_failure(buf, "UINT should be greater than expected.");
        append_argument(buf, "Expected", expected_name, "%u", expected);
        append_argument(buf, "Actual", actual_name, "%u", actual);
        append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_uint_not_equal(CHAR *expected_name, UINT expected, CHAR *actual_name, UINT actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);
        append_location(buf, file, line);
        append_failure(buf, "UINT should not be equal to expected.");
        append_argument(buf, "Expected", expected_name, "%u", expected);
        append_argument(buf, "Actual", actual_name, "%u", actual);
        append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_int_equal(CHAR *expected_name, INT expected, CHAR *actual_name, INT actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected != actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);

        append_failure(buf, "INT should be equal to expected.");
        append_location(buf, file, line);
        append_argument(buf, "Expected", expected_name, "%d", expected);
        append_argument(buf, "Actual", actual_name, "%d", actual);
        append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}