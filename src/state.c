#include "state.h"
#include "GLBW/Core/def.h"

#include <stddef.h>

static glbwState state = {
    .init = GLBW_FALSE,
    .autolog_errors = GLBW_TRUE,
    .enable_error_buffer = GLBW_TRUE,
};

glbwState* glbw_getState(void) { return &state; }

void glbw_defaultState(void) {
    state.autolog_errors = 1;
    state.enable_error_buffer = 1;
    state.init = 0;
}