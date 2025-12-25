#include "window.h"
#include "state.h"
#include "error.h"

#include "GLBW/Core/def.h"
#include "GLBW/Core/win.h"

#include <stdlib.h>


static glbw_window window = {
    .width = 0,
    .height = 0,
    .msaa = 0,
    .resizable = GLBW_FALSE,
    .init = GLBW_FALSE,
    .shouldClose = GLBW_FALSE,
    .vsync = GLBW_FALSE,
    .winmode = GLBW_WINMOD_NORMAL_WINDOWED,
    .glfwWin = NULL, 
    .glfwMon = NULL
};

int GLBW_CreateWindow(const char* title, int width, int height)
{
    if ( GLBW_CreateWindowWithArgs(title, width, height, GLBW_WINMOD_NORMAL_WINDOWED, GLBW_FALSE, GLBW_FALSE, 0) )
        return GLBW_SUCCESS;
    else return GLBW_FAIL;
}


int GLBW_CreateWindowWithArgs(const char* title, int width, int height, GLBWenum mode, GLBWenum vsync, GLBWenum resizable, int msaa)
{
    if (window.init != GLBW_FALSE) {
        glbw_logError("window already created!");
        return GLBW_FAIL;
    }

    if(width <= 0 || width >= 9000 || height <= 0 || height >= 9000) {
        glbw_logError("invalid window resolution: %dx%d", width, height);
        return GLBW_FAIL;
    }
    
    if( (title == NULL) || (title[0] == '\0') ) title = "GLBW Window";
    if(mode < GLBW_WINMOD_FULLSCREEN || mode > GLBW_WINMOD_NORMAL_WINDOWED) mode = GLBW_WINMOD_NORMAL_WINDOWED;

    window.glfwMon = glfwGetPrimaryMonitor();
    const GLFWvidmode* video = glfwGetVideoMode(window.glfwMon);

    window.width = width;
    window.height = height;
    window.msaa = msaa;
    window.vsync = vsync;
    window.resizable = resizable;
    window.winmode = mode;

    glfwWindowHint(GLFW_REFRESH_RATE, video->refreshRate);
    glfwWindowHint(GLFW_SAMPLES, window.msaa);
    glfwWindowHint(GLFW_RESIZABLE, window.resizable);

    int x = 0, y = 0, w = 0, h = 0;
    switch (mode) 
    {
        case GLBW_WINMOD_FULLSCREEN:
            glfwWindowHint(GLFW_RED_BITS, video->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, video->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, video->blueBits);
            window.width = video->width;  // Use our 'desktop' resolution for window size
            window.height = video->height; // to get a 'full screen borderless' window.
            window.glfwWin = glfwCreateWindow(window.width, window.height, title, window.glfwMon, NULL);
            break;
        case GLBW_WINMOD_BORDERLESS_MAXIMIZED: {
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
            glfwGetMonitorWorkarea(window.glfwMon, &x, &y, &w, &h);
            window.width = w;
            window.height = h;
            window.glfwWin = glfwCreateWindow(w, h, title, NULL, NULL);
            glfwSetWindowPos(window.glfwWin, x, y);
            break;
        }
        case GLBW_WINMOD_MAXIMIZED_WINDOWED:
            glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
            glfwGetMonitorWorkarea(window.glfwMon, &x, &y, &w, &h);
            window.width = w;
            window.height = h;
            window.glfwWin = glfwCreateWindow(w, h, title, NULL, NULL);
            glfwSetWindowPos(window.glfwWin, x, y);
            glfwMaximizeWindow(window.glfwWin);
            break;
        default:
            glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
            window.glfwWin = glfwCreateWindow(window.width, window.height, title, NULL, NULL);
    }

    glfwSwapInterval(window.vsync);
    glfwMakeContextCurrent(window.glfwWin);
    glfwGetWindowSize(window.glfwWin, &(window.width), &(window.height));
    window.init = 1;
    return GLBW_SUCCESS;
}

void glbw_defaultWin(void)
{
    window.width = 0;
    window.height = 0;
    window.resizable = GLBW_FALSE;
    window.init = GLBW_FALSE;
    window.shouldClose = GLBW_FALSE;
    window.msaa = 0;
    window.vsync = GLBW_FALSE;
    window.winmode = GLBW_WINMOD_NORMAL_WINDOWED;
    window.glfwWin = NULL; 
    window.glfwMon = NULL;
}

int GLBW_UpdateWindow(void)
{
    if ( glfwWindowShouldClose(window.glfwWin) ) window.shouldClose = GLBW_TRUE;

    glfwPollEvents();


    glfwSwapBuffers(window.glfwWin);

    return !window.shouldClose;
}

glbw_window* glbw_getWin(void) { return &window; }