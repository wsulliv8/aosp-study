#pragma once

#include <EGL/egl.h>
#include <KHR/khrplatform.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EGLAPIENTRYP
#define EGLAPIENTRYP *
#endif

typedef void* EGLImageKHR;
typedef void* EGLSyncKHR;
typedef void* EGLStreamKHR;
typedef void* EGLClientBuffer;
typedef void (*EGLDEBUGPROCKHR)(EGLenum error, const char* command, EGLint messageType,
                                EGLLabelKHR threadLabel, EGLLabelKHR objectLabel,
                                const char* message);
typedef void* EGLObjectKHR;
typedef void* EGLLabelKHR;

typedef EGLint(EGLAPIENTRYP PFNEGLDUPNATIVEFENCEFDANDROIDPROC)(EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLSyncKHR(EGLAPIENTRYP PFNEGLCREATESYNCKHRPROC)(EGLDisplay dpy, EGLenum type,
                                                         const EGLint* attrib_list);
typedef EGLBoolean(EGLAPIENTRYP PFNEGLDESTROYSYNCKHRPROC)(EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLint(EGLAPIENTRYP PFNEGLCLIENTWAITSYNCKHRPROC)(EGLDisplay dpy, EGLSyncKHR sync,
                                                         EGLint flags, EGLTimeKHR timeout);

#define EGL_SYNC_NATIVE_FENCE_ANDROID 0x3144
#define EGL_SYNC_NATIVE_FENCE_FD_ANDROID 0x3145
#define EGL_NO_NATIVE_FENCE_FD_ANDROID (-1)
#define EGL_SYNC_FENCE_KHR 0x30F9
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR 0x30F0
#define EGL_FOREVER_KHR 0xFFFFFFFFFFFFFFFFull
#define EGL_TIMEOUT_EXPIRED_KHR 0x305E
#define EGL_CONDITION_SATISFIED_KHR 0x30F6

inline EGLint eglClientWaitSyncKHR(EGLDisplay /*dpy*/, EGLSyncKHR /*sync*/, EGLint /*flags*/,
                                   EGLTimeKHR /*timeout*/) {
    return EGL_CONDITION_SATISFIED_KHR;
}
inline EGLBoolean eglDestroySyncKHR(EGLDisplay /*dpy*/, EGLSyncKHR /*sync*/) { return EGL_TRUE; }
inline EGLSyncKHR eglCreateSyncKHR(EGLDisplay /*dpy*/, EGLenum /*type*/,
                                   const EGLint* /*attrib_list*/) {
    return EGL_NO_SYNC_KHR;
}
inline EGLint eglDupNativeFenceFDANDROID(EGLDisplay /*dpy*/, EGLSyncKHR /*sync*/) { return -1; }

#ifdef __cplusplus
}
#endif
