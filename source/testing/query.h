//
// Created by Andrew Wade on 2019-01-26.
//

#ifndef TESTABLE_QUERY_H
#define TESTABLE_QUERY_H

#include "testable.h"
#include "../utilities/_pp.h"


/**
 * We need to create a struct for the subject and for the input(s)
 * Then the query should be a struct containing both subject and input struct
 * Then EXPECT_THAT should use the query name to create a new query by passing the input value
 * EXPECT_THAT should then pass in the string name and value of the subject along with the string passed for the query creation function
 * Then the query output will parse the string to determine the name of the input variable and it will already have the name of the subject variable
 *
 */
#define QUERY(query_name, subject_type, input_type)                                                   \
                                                                                                \
typedef void (*_query_##query_name##_subject_t)(subject_type);                                        \
/* define function prototype */                                                                 \
IF(TYPE_IS_VOID(subject_type)) (                                                                \
    IF(TYPE_IS_VOID(input_type)) (                                                              \
                                                                                                \
        /* declare function prototype */                                                        \
        void _query_##query_name##_function(void);                                                    \
                                                                                                \
        /* define query */                                                                      \
        _query_##query_name##_subject_t query_name(void) {                                                  \
            return _query_##query_name##_function;                                                    \
        }                                                                                       \
                                                                                                \
        /* let user define implementation */                                                    \
        void _query_##query_name##_function(void)                                                     \
    )                                                                                           \
    IF(NOT(TYPE_IS_VOID(input_type))) (                                                         \
        typedef struct {                                                                        \
            const char *name;                                                                   \
            struct {                                                                            \
                const char *name;                                                               \
                input_type value;                                                               \
            } input;                                                                            \
        }_query_##query_name##_t;                                                               \
        /* declare function prototype */                                                        \
        void _query_##query_name##_function(_query_##query_name##_t *query);                    \
                                                                                                \
        /* create query function */                                                             \
        _query_##query_name##_t query_name(input_type input) {                                  \
            _query_##query_name##_t query = {                                                   \
                .name = #query_name,                                                            \
                .input = {                                                                      \
                    .value = input                                                              \
                }                                                                               \
            };                                                                                  \
            return query;                                                                       \
        }                                                                                       \
                                                                                                \
        /* let user define implementation */                                                    \
        void _query_##query_name##_function(_query_##query_name##_t *query)                     \
    )                                                                                           \
)                                                                                               \
IF(NOT(TYPE_IS_VOID(subject_type))) (                                                           \
    IF(TYPE_IS_VOID(input_type)) (                                                              \
        /* declare function prototype */                                                        \
        void _query_##query_name##_function(subject_type subject);                              \
                                                                                                \
        /* define subject prototype */                                                          \
        void _query_##query_name##_subject(subject_type subject) {                              \
            _query_##query_name##_function(subject);                                            \
        }                                                                                       \
                                                                                                \
        /* define query */                                                                      \
        _query_##query_name##_subject_t query_name(void) {                                                  \
            return _query_##query_name##_subject;                                                     \
        }                                                                                       \
                                                                                                \
        /* let user define implementation */                                                    \
        void _query_##query_name##_function(subject_type subject)                                     \
    )                                                                                           \
    IF(NOT(TYPE_IS_VOID(input_type))) (                                                         \
        /* declare function prototype */                                                        \
        void _query_##query_name##_function(subject_type subject, input_type input);                  \
                                                                                                \
        /* define input singleton */                                                            \
        input_type *_query_##query_name##_input() {                                                   \
            static input_type input;                                                            \
            return &input;                                                                      \
        }                                                                                       \
                                                                                                \
        /* define subject prototype */                                                          \
        void _query_##query_name##_subject(subject_type subject) {                                    \
            input_type input = *_query_##query_name##_input();                                        \
            _query_##query_name##_function(subject, input);                                           \
        }                                                                                       \
                                                                                                \
        /* define query */                                                                      \
        _query_##query_name##_subject_t query_name(input_type input) {                                      \
            *_query_##query_name##_input() = input;                                                   \
            return _query_##query_name##_subject;                                                     \
        }                                                                                       \
                                                                                                \
        /* let user define implementation */                                                    \
        void _query_##query_name##_function(subject_type subject, input_type input)                   \
    )                                                                                           \
)
#define EXPECT_THAT(subject, query) query(subject)

#define SUBJECT(type) type
#define INPUT(type) type


#ifdef __cplusplus
};
#endif

#endif //TESTABLE_QUERY_H
