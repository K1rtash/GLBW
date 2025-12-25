#ifndef GLBW_INTERNAL_WINDOW_H
#define GLBW_INTERNAL_WINDOW_H

#include "GLBW/Core/win.h"

#include <GLFW/glfw3.h>

typedef struct
{
    int width;
    int height;
    int msaa;
    GLBWenum init;
    GLBWenum shouldClose;
    GLBWenum vsync;
    GLBWenum resizable;
    GLBWenum winmode;
    GLFWwindow* glfwWin;
    GLFWmonitor* glfwMon;
}  glbw_window;

static glbw_window window;

glbw_window* glbw_getWin(void);

void glbw_defaultWin(void);

#endif