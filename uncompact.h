#ifndef UNCOMPACT_H
#define UNCOMPACT_H

#ifdef _WIN32
    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else 
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else 
    #define DLL_EXPORT
#endif

#include <stdio.h>

DLL_EXPORT int uncompact_file(const char *path, const char *destination_path);

#endif