#include "testable.h"
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include "../utilities/_list.h"
#include "../utilities/_stack.h"

#define STRING_NAME(name) #name
#define TO_STRING(x) STRING_NAME(x)

#define ASSERT_FAILED(code, msg)           \
assert_fail_callback(code, msg);           \
longjmp(*(_assert_get_fail_point()), code)

static _stack_t fail_jump_stack = {
    .owner = NULL,
    .elements = NULL,
    .size = 0
};

static _list_t fail_callback_queue = {
    .owner = NULL,
    .elements = NULL,
    .size = 0
};

typedef struct assert_failure_t {
    int code;
    char *message;
} assert_failure_t;

//static _node_t *fail_jump_stack          = NULL;
//static _node_t *fail_callback_queue      = NULL;
//static INT     fail_callback_queue_count = 0;

static char null[] = "NULL";
static const fail_callback_t ignore_failure = {NULL, NULL};

static VOID call_assert_failure_callback(VOID *element, VOID *input) {
    fail_callback_t *callback = element;
    assert_failure_t *failure = input;
    if(callback != NULL && failure != NULL) {
        callback->call(callback->user, failure->code, failure->message);
    }
}

static VOID assert_fail_callback(int code, char *message) {
    struct assert_failure_t failure = {code, message};
    if(_list_first(&fail_callback_queue) != &ignore_failure) {
        _list_for_each(&fail_callback_queue, call_assert_failure_callback, &failure);
    }
}

static void messege_append_location(char *buf, char *file, unsigned int line) {
    unsigned int max_length = ASSERT_MSG_BUFFER_SIZE;
    /* go to end of string */
    while (*buf != '\0') {
        max_length--;
        buf++;
    }
    snprintf(buf, max_length, "     Location: %s(%d):\n", file, line);
}

static void messege_append_failure(char *buf, char *fmt, ...) {
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
static void messege_append_condition(char *buf, char *explanation, int condition) {
    va_list      args;
    unsigned int write_length = 0;
    unsigned int max_length   = ASSERT_MSG_BUFFER_SIZE;

    /* go to end of string */
    while (*buf != '\0') {
        max_length--;
        buf++;
    }

    /* if argument is NULL */
    if (!strcmp(TO_STRING(NULL), explanation)) {
        /* change argument name to "NULL" instead of "((void*)0)" */
        explanation = null;
    }

    write_length = snprintf(buf, max_length, "    Condition: %s\n", explanation);
    buf += write_length;
    max_length -= write_length;
    snprintf(buf, max_length, "       Result: %s\n", (condition) ? "true":"false");

}
static void messege_append_argument(char *buf, char *arg, char *arg_name, char *fmt, ...) {
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

static void messege_append_message(char *buf, char *fmt, ...) {
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

static void messege_append_vmessage(char *buf, char *fmt, va_list args) {
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

VOID _assert_expect_failure(jmp_buf *jump) {
    _stack_push(&fail_jump_stack, jump);
    _list_insert(&fail_callback_queue, 0, (void *) &ignore_failure);
}

VOID _assert_cleanup_expected_failure(jmp_buf *jump) {
    ASSERT_EQ(jump, _stack_top(&fail_jump_stack));
    _list_remove(&fail_callback_queue, (void *) &ignore_failure);
    _stack_pop(&fail_jump_stack);
}

VOID _assert_push_fail_point(jmp_buf *jump) {
    _stack_push(&fail_jump_stack, jump);
//    _node_t *node = _node_allocate();
//    _node_initialize(node, jump);
//    if (fail_jump_stack == NULL) {
//        fail_jump_stack = node;
//    } else {
//        _list_insert(fail_jump_stack, node);
//    }
}

jmp_buf *_assert_pop_fail_point() {
    return _stack_pop(&fail_jump_stack);
//    _node_t *pop_node;
//    jmp_buf *pop_point;
//
//    if (fail_jump_stack == NULL) {
//        return NULL;
//    } else {
//        pop_node  = _list_last(fail_jump_stack);
//        pop_point = _node_data(pop_node);
//
//        if (pop_node == fail_jump_stack) {
//            // empty, return jump stack to NULL
//            fail_jump_stack = NULL;
//        } else {
//            _list_remove(pop_node);
//        }
//
//        _node_release(pop_node);
//        return pop_point;
//    }
}

jmp_buf *_assert_get_fail_point() {
    return _stack_top(&fail_jump_stack);
//    if (fail_jump_stack == NULL) {
//        return NULL;
//    } else {
//        return _list_last(fail_jump_stack)->data;
//    }
}

VOID _assert_add_fail_callback(fail_callback_t *callback) {
    _list_append(&fail_callback_queue, callback);
//    _node_t *node = _node_allocate();
//    _node_initialize(node, callback);
//    if (fail_callback_queue == NULL) {
//        fail_callback_queue = node;
//    } else {
//        _list_insert(fail_callback_queue, node);
//        fail_callback_queue = node;
//    }
//    fail_callback_queue_count++;
}

VOID _assert_remove_fail_callback(fail_callback_t *callback) {
    _list_remove(&fail_callback_queue, callback);
//    _node_t *node = fail_callback_queue;
//    do {
//        if (node->data == callback) {
//            if (node == fail_callback_queue) {
//                fail_callback_queue = node->next;
//            }
//            _list_remove(node);
//            _node_release(node);
//            fail_callback_queue_count--;
//            break;
//        }
//        node = _node_next(node);
//    } while (node != fail_callback_queue);
//    if (fail_callback_queue_count == 0) {
//        fail_callback_queue = NULL;
//    }

}

VOID _assert_true(CHAR *explanation, BOOL condition, CHAR *file, UINT line, char *message, ...) {
    if (!condition) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};
        va_start(args, message);
        messege_append_location(buf, file, line);
        messege_append_failure(buf, "Condition should be true!");
        messege_append_condition(buf, explanation, condition);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_false(CHAR *explanation, BOOL condition, CHAR *file, UINT line, char *message, ...) {
    if (condition) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};
        va_start(args, message);
        messege_append_location(buf, file, line);
        messege_append_failure(buf, "Condition should be true!");
        messege_append_argument(buf, "Condition", explanation, "%s", "true");
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_char_equal(CHAR *expected_name, CHAR expected, CHAR *actual_name, CHAR actual, CHAR *file, UINT line, char *message, ...) {
    if (expected != actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};
        va_start(args, message);
        messege_append_location(buf, file, line);
        messege_append_failure(buf, "Chars should be equal!");
        messege_append_argument(buf, "Expected", expected_name, "%c", expected);
        messege_append_argument(buf, "Actual", actual_name, "%c", actual);
        messege_append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_char_not_equal(CHAR *expected_name, CHAR expected, CHAR *actual_name, CHAR actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);
        messege_append_location(buf, file, line);
        messege_append_failure(buf, "Chars should not be equal!");
        messege_append_argument(buf, "Expected", expected_name, "%c", expected);
        messege_append_argument(buf, "Actual", actual_name, "%c", actual);
        messege_append_vmessage(buf, message, args);
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
        messege_append_location(buf, file, line);
        messege_append_failure(buf, "Pointers should be equal");
        messege_append_argument(buf, "Expected", expected_name, "%p", expected);
        messege_append_argument(buf, "Actual", actual_name, "%p", actual);
        messege_append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_pointer_not_equal(CHAR *expected_name, VOID *expected, CHAR *actual_name, VOID *actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);
        messege_append_location(buf, file, line);
        messege_append_failure(buf, "Pointers should not be equal.");
        messege_append_argument(buf, "Expected", expected_name, "%p", expected);
        messege_append_argument(buf, "Actual", actual_name, "%p", actual);
        messege_append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_uint_greater_than(CHAR *expected_name, UINT expected, CHAR *actual_name, UINT actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);
        messege_append_location(buf, file, line);
        messege_append_failure(buf, "UINT should be greater than expected.");
        messege_append_argument(buf, "Expected", expected_name, "%u", expected);
        messege_append_argument(buf, "Actual", actual_name, "%u", actual);
        messege_append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_uint_not_equal(CHAR *expected_name, UINT expected, CHAR *actual_name, UINT actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected == actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);
        messege_append_location(buf, file, line);
        messege_append_failure(buf, "UINT should not be equal to expected.");
        messege_append_argument(buf, "Expected", expected_name, "%u", expected);
        messege_append_argument(buf, "Actual", actual_name, "%u", actual);
        messege_append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_int_equal(CHAR *expected_name, INT expected, CHAR *actual_name, INT actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected != actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);

        messege_append_failure(buf, "INT should be equal to expected.");
        messege_append_location(buf, file, line);
        messege_append_argument(buf, "Expected", expected_name, "%d", expected);
        messege_append_argument(buf, "Actual", actual_name, "%d", actual);
        messege_append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_ulong_equal(CHAR *expected_name, ULONG expected, CHAR *actual_name, ULONG actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected != actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);

        messege_append_failure(buf, "ULONG should be equal to expected.");
        messege_append_location(buf, file, line);
        messege_append_argument(buf, "Expected", expected_name, "%ul", expected);
        messege_append_argument(buf, "Actual", actual_name, "%ul", actual);
        messege_append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_ulong_greater_or_equal(CHAR *expected_name, ULONG expected, CHAR *actual_name, ULONG actual, CHAR *file, UINT line, CHAR *message, ...) {
    if (expected > actual) {
        va_list args;
        char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

        va_start(args, message);

        messege_append_failure(buf, "ULONG should be greater than or equal to expected.");
        messege_append_location(buf, file, line);
        messege_append_argument(buf, "Expected", expected_name, "%ul", expected);
        messege_append_argument(buf, "Actual", actual_name, "%ul", actual);
        messege_append_vmessage(buf, message, args);
        va_end(args);
        ASSERT_FAILED(0, buf);
    }
}

VOID _assert_force_failure(CHAR *what, CHAR *file, UINT line, CHAR *message, ...) {
    va_list args;
    char    buf[ASSERT_MSG_BUFFER_SIZE] = {0};

    va_start(args, message);

    messege_append_failure(buf, "Forced Failure from %s", what);
    messege_append_location(buf, file, line);
    messege_append_vmessage(buf, message, args);
    va_end(args);
    ASSERT_FAILED(0, buf);
}