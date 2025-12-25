#ifndef GLBW_WINDOW_H
#define GLBW_WINDOW_H

#include "def.h"

#ifdef _WIN32
#  ifdef GLBW_BUILD
#    define GLBW_API __declspec(dllexport)
#  else
#    define GLBW_API __declspec(dllimport)
#  endif
#else
#  define GLBW_API __attribute__((visibility("default")))
#endif

#define GLBW_WINMOD_FULLSCREEN 0
#define GLBW_WINMOD_BORDERLESS_MAXIMIZED 1
#define GLBW_WINMOD_MAXIMIZED_WINDOWED 2
#define GLBW_WINMOD_NORMAL_WINDOWED 3

/**
 * @brief Creates a window
 * 
 * @param title Title to be displayed at the window's sistem UI
 * @param width Window width in pixels
 * @param height Window height in pixels
 * 
 * @see GLBW_CreateWindowWithArgs
 */
int GLBW_CreateWindow(const char* title, int width, int height);

/**
 * @brief Creates a window with precise arguments
 * 
 * @param title Title to be displayed at the window's sistem UI
 * @param width Window width in pixels
 * @param height Window height in pixels
 * @param mode GLBW_WINMOD, as in GLBW_WINMOD_FULLSCREEN
 * @param vsync GLBW_TRUE or GLBW_FALSE, must be supported by your system
 * @param resizable GLBW_TRUE or GLBW_FALSE
 * @param msaa Multi-sample anti alising, must be supported by your system 
 */
int GLBW_CreateWindowWithArgs(const char* title, int width, int height, GLBWenum mode, GLBWenum vsync, GLBWenum resizable, int msaa);

/**
 * @brief Clears the window and polls input and system events
 * 
 * @returns GLBW_TRUE or GLBW_FALSE if a close event was triggered
 */
int GLBW_UpdateWindow(void);

#endif