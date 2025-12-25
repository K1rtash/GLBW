#ifndef GLBW_H
#define GLBW_H

/**
 * @file glbw.h
 * @brief Basic GLFW functions
 *
 * @author David Sánchez
 * @date 2025
 */

#include "Core/def.h"
#include "Core/win.h"

#ifdef _WIN32
#  ifdef GLBW_BUILD
#    define GLBW_API __declspec(dllexport)
#  else
#    define GLBW_API __declspec(dllimport)
#  endif
#else
#  define GLBW_API __attribute__((visibility("default")))
#endif

/**
 * @brief Initializes the library
 * 
 * The library must be initialized before GLBW functions are used.
 * 
 * This function will call @ref GLBW_Exit() on failure
 * 
 * @returns @ref GLBWenum
 * @retval GLBW_SUCCESS Library initialized
 * @retval GLBW_FAIL Library failed to initialize
 * 
 * @see GLBW_Exit() @see GLBW_CreateWindow()
 */
GLBW_API GLBWenum GLBW_Init();

/**
 * @brief Frees all resources created by the library, like the window and textures
 * 
 * Should be called before the program ends to free resources allocated by this library
 * 
 * The library must be initialized again with @ref GLBW_Init() before being able to use any functions again
 * 
 * @see GLBW_Init()
 */
GLBW_API void GLBW_Exit();

/**
 * @brief Prints the latest error to the console
 */
GLBW_API void GLBW_GetError();
#endif