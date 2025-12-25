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
 * @returns @ref GLBW_SUCCESS or @ref GLBW_FAIL
 * 
 * @see GLBW_CreateWindowWithArgs
 */
GLBW_API int GLBW_CreateWindow(const char* title, int width, int height);

/**
 * @brief Creates a window with precise arguments
 * 
 * @param title Title to be displayed at the window's sistem UI
 * @param width Window width in pixels
 * @param height Window height in pixels
 * @param mode Window mode, as in @ref GLBW_WINMOD_FULLSCREEN
 * @param vsync @ref GLBW_TRUE or @ref GLBW_FALSE, must be supported by your system
 * @param resizable @ref GLBW_TRUE or @ref GLBW_FALSE
 * @param msaa Multi-sample anti alising, must be supported by your system 
 * 
 * @returns @ref GLBW_SUCCESS or @ref GLBW_FAIL
 */
GLBW_API int GLBW_CreateWindowWithArgs(const char* title, int width, int height, GLBWenum mode, GLBWenum vsync, GLBWenum resizable, int msaa);

/**
 * @brief Clears the window and polls input and system events
 * 
 * @returns @ref GLBW_TRUE or @ref GLBW_FALSE if a close event was triggered
 */
GLBW_API int GLBW_UpdateWindow(void);

#endif