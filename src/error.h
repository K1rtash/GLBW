#ifndef GLBW_INTERNAL_ERROR
#define GLBW_INTERNAL_ERROR

void glbw_logError(const char* format, ...);
const char* glbw_getError();

#endif