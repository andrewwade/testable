//
// Created by Andrew Wade on 7/10/18.
//

#ifndef TESTABLE_OUTPUT_H
#define TESTABLE_OUTPUT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *message;
    char *tag;
    char *level;
    char *location;
} output_t;


typedef void (*output_handler_t)(output_t *output);

void output_subscribe()

#ifdef __cplusplus
};
#endif

#endif //TESTABLE_OUTPUT_H
