#ifndef GLBW_DEFINITIONS_H
#define GLBW_DEFINITIONS_H

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
 * @file def.h
 * @brief Definitions and enums
 *
 * @author David Sánchez
 * @date 2025
 */

    typedef int GLBWenum;

    #define GLBW_TRUE 1
    #define GLBW_FALSE 0
    
    #define GLBW_FAIL 1
    #define GLBW_SUCCESS 0

#endif