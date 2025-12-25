#include "error.h"
#include "state.h"
#include "GLBW/glbw.h"

#include <stdio.h> 
#include <stdarg.h> 
#include <string.h>

static char buffer[512] = {0};

void glbw_logError(const char* format, ...)
{
    if( !glbw_getState()->enable_error_buffer ) return;

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 512, format, args);
    va_end(args);

    if( glbw_getState()->autolog_errors )
        GLBW_GetError();    
}

const char* glbw_getError() { 
    return buffer;
}