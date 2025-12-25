#include "GLBW/glbw.h"
#include "state.h"
#include "error.h"
#include "window.h"

#include <GLFW/glfw3.h>
#include <stdio.h>

int GLBW_Init()
{
    if ( glbw_getState()->init != 0 ) {
        glbw_logError("lib is already init!");
        return GLBW_FAIL;
    }

    if (!glfwInit()) {
        glbw_logError("failed to init dep: GLFW");
        return GLBW_FAIL;
    }
        
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return GLBW_SUCCESS;
}

void GLBW_Exit()
{
    if( glbw_getState()->init != GLBW_TRUE ) return;

    glbw_defaultState();

    if ( glbw_getWin()->init == GLBW_TRUE ) 
    {
        glfwDestroyWindow(glbw_getWin()->glfwWin);
        glbw_defaultWin();
    }
    glfwTerminate();
}

void GLBW_GetError()
{
    printf("%s\n", glbw_getError());
}