#ifndef GLBW_INTERNAL_STATE_H
#define GLBW_INTERNAL_STATE_H

#include <GLFW/glfw3.h>

typedef struct {
    int init;
    int autolog_errors;
    int enable_error_buffer;
} glbwState;

static glbwState state;

glbwState* glbw_getState(void);

void glbw_defaultState(void);

#endif