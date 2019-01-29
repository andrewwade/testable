//
// Created by Andrew Wade on 2019-01-26.
//

#ifndef TESTABLE_QUERY_H
#define TESTABLE_QUERY_H

#include "testable.h"
#include "_pp.h"

#define SUBJECT(type, name) type, name, type name
#define _TYPE FIRST
#define _NAME SECOND
#define _ARG THIRD

#define INPUT(type, name) type, name
#define INPUT_TYPE FIRST
#define INPUT_NAME SECOND

#define QUERY(name, subject_type, input_type)                                                   \
typedef void (*_query_##name##_subject_t)(subject_type);                                        \
/* define function prototype */                                                                 \
IF(TYPE_IS_VOID(_TYPE(subject))) (                                                              \
    IF(TYPE_IS_VOID(_TYPE(input))) (                                                            \
                                                                                                \
        /* declare function prototype */                                                        \
        void _query_##name##_function(void);                                                    \
                                                                                                \
        /* define query */                                                                      \
        _query_##name##_subject_t name(void) {                                                  \
            return _query_##name##_function;                                                    \
        }                                                                                       \
                                                                                                \
        /* let user define implementation */                                                    \
        void _query_##name##_function(void)                                                     \
    )                                                                                           \
    IF(NOT(TYPE_IS_VOID(_TYPE(input)))) (                                                       \
        /* declare function prototype */                                                        \
        void _query_##name##_function(input_type input);                                        \
                                                                                                \
        /* define input singleton */                                                            \
        input_type *_query_##name##_input() {                                                   \
            static input_type input;                                                            \
            return &input;                                                                      \
        }                                                                                       \
                                                                                                \
        /* define subject prototype */                                                          \
        void _query_##name##_subject(void) {                                                    \
            input_type input = *query_##name##_input();                                         \
            _query_##name##_function(input);                                                    \
        }                                                                                       \
                                                                                                \
        /* define query */                                                                      \
        _query_##name##_subject_t name(input_type input) {                                      \
            *_query_##name##_input() = input;                                                   \
            return _query_##name##_subject;                                                     \
        }                                                                                       \
                                                                                                \
        /* let user define implementation */                                                    \
        void _query_##name##_function(c)                                                        \
    )                                                                                           \
)                                                                                               \
IF(NOT(TYPE_IS_VOID(subject_type))) (                                                           \
    IF(TYPE_IS_VOID(input_type)) (                                                              \
        /* declare function prototype */                                                        \
        void _query_##name##_function(subject_type subject);                                    \
                                                                                                \
        /* define subject prototype */                                                          \
        void _query_##name##_subject(subject_type subject) {                                    \
            _query_##name##_function(subject);                                                  \
        }                                                                                       \
                                                                                                \
        /* define query */                                                                      \
        _query_##name##_subject_t name(void) {                                                  \
            return _query_##name##_subject;                                                     \
        }                                                                                       \
                                                                                                \
        /* let user define implementation */                                                    \
        void _query_##name##_function(subject_type subject)                                     \
    )                                                                                           \
    IF(NOT(TYPE_IS_VOID(input_type))) (                                                         \
        /* declare function prototype */                                                        \
        void _query_##name##_function(subject_type subject, input_type input);                  \
                                                                                                \
        /* define input singleton */                                                            \
        input_type *_query_##name##_input() {                                                   \
            static input_type input;                                                            \
            return &input;                                                                      \
        }                                                                                       \
                                                                                                \
        /* define subject prototype */                                                          \
        void _query_##name##_subject(subject_type subject) {                                    \
            input_type input = *_query_##name##_input();                                        \
            _query_##name##_function(subject, input);                                           \
        }                                                                                       \
                                                                                                \
        /* define query */                                                                      \
        _query_##name##_subject_t name(input_type input) {                                      \
            *_query_##name##_input() = input;                                                   \
            return _query_##name##_subject;                                                     \
        }                                                                                       \
                                                                                                \
        /* let user define implementation */                                                    \
        void _query_##name##_function(subject_type subject, input_type input)                   \
    )                                                                                           \
)
#define EXPECT_THAT(subject, query) query(subject)

#define SUBJECT(type) type
#define INPUT(type) type


#ifdef __cplusplus
};
#endif

#endif //TESTABLE_QUERY_H
