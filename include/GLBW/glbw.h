#ifndef GLBW_H
#define GLBW_H

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
 * This function will call GLBW_Exit() on failure
 * 
 * @returns GLBW_TRUE on success
 */
int GLBW_Init();

/**
 * @brief Frees all resources created by the library, like the window and textures
 * 
 * Should be called before the program ends to free resources allocated by this library
 */
void GLBW_Exit();

/**
 * @brief Prints the latest error to the console
 */
void GLBW_GetError();
#endif