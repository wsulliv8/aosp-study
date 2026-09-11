#pragma once

#include <EGL/eglplatform.h>
#include <KHR/khrplatform.h>
#include <stdint.h>

typedef void* EGLDisplay;
typedef void* EGLConfig;
typedef void* EGLContext;
typedef void* EGLSurface;
typedef void* EGLImage;
typedef void* EGLImageKHR;
typedef void* EGLSync;
typedef void* EGLSyncKHR;
typedef void* EGLStreamKHR;
typedef void* EGLClientBuffer;
typedef unsigned int EGLenum;
typedef int32_t EGLint;
typedef unsigned int EGLBoolean;
typedef intptr_t EGLAttrib;
typedef intptr_t EGLAttribKHR;
typedef uint64_t EGLTimeKHR;
typedef void* EGLObjectKHR;
typedef void* EGLLabelKHR;

#define EGLAPI
#define EGLAPIENTRY
#define EGLAPIENTRYP *

#define EGL_NO_DISPLAY ((EGLDisplay)0)
#define EGL_NO_CONTEXT ((EGLContext)0)
#define EGL_NO_SURFACE ((EGLSurface)0)
#define EGL_NO_SYNC_KHR ((EGLSyncKHR)0)
#define EGL_NO_IMAGE_KHR ((EGLImageKHR)0)
#define EGL_FALSE 0
#define EGL_TRUE 1
#define EGL_SUCCESS 0x3000
#define EGL_NONE 0x3038
#define EGL_WIDTH 0x3057
#define EGL_HEIGHT 0x3056
#define EGL_LINUX_DMA_BUF_EXT 0x3270

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
void* eglGetProcAddress(const char* procname);

#ifdef __cplusplus
}
#endif
