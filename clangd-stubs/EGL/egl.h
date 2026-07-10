#pragma once

#include <EGL/eglplatform.h>

typedef void* EGLDisplay;
typedef void* EGLConfig;
typedef void* EGLContext;
typedef void* EGLSurface;
typedef void* EGLImageKHR;
typedef void* EGLSyncKHR;
typedef void* EGLStreamKHR;
typedef unsigned int EGLenum;
typedef int EGLint;
typedef unsigned int EGLBoolean;

#define EGL_NO_DISPLAY ((EGLDisplay)0)
#define EGL_NO_CONTEXT ((EGLContext)0)
#define EGL_NO_SURFACE ((EGLSurface)0)
#define EGL_FALSE 0
#define EGL_TRUE 1

#ifdef __cplusplus
extern "C" {
#endif

EGLDisplay eglGetDisplay(EGLNativeDisplayType display);
EGLBoolean eglInitialize(EGLDisplay dpy, EGLint* major, EGLint* minor);
EGLBoolean eglTerminate(EGLDisplay dpy);
EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context,
                            const EGLint* attrib_list);
EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext ctx);
EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
EGLBoolean eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);
EGLint eglGetError(void);

#ifdef __cplusplus
}
#endif
