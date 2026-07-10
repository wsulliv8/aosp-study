#pragma once

#include <KHR/khrplatform.h>

typedef int EGLint;
typedef unsigned int EGLBoolean;
typedef void* EGLDisplay;
typedef void* EGLConfig;
typedef void* EGLContext;
typedef void* EGLSurface;

#if defined(_WIN32) || defined(__CYGWIN__)
typedef void* EGLNativeDisplayType;
typedef void* EGLNativeWindowType;
typedef void* EGLNativePixmapType;
#else
typedef void* EGLNativeDisplayType;
typedef khronos_uintptr_t EGLNativeWindowType;
typedef khronos_uintptr_t EGLNativePixmapType;
#endif
