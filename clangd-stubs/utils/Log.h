#pragma once

#include <cstdio>

#ifndef ALOG
#define ALOG(priority, tag, ...) ((void)0)
#endif

#ifndef ALOGV
#define ALOGV(...) ((void)0)
#endif
#ifndef ALOGD
#define ALOGD(...) ((void)0)
#endif
#ifndef ALOGI
#define ALOGI(...) ((void)0)
#endif
#ifndef ALOGW
#define ALOGW(...) ((void)0)
#endif
#ifndef ALOGE
#define ALOGE(...) ((void)0)
#endif
#ifndef ALOGW_IF
#define ALOGW_IF(cond, ...) ((void)0)
#endif
#ifndef ALOGE_IF
#define ALOGE_IF(cond, ...) ((void)0)
#endif
#ifndef LOG_ALWAYS_FATAL
#define LOG_ALWAYS_FATAL(...) ((void)0)
#endif
#ifndef LOG_ALWAYS_FATAL_IF
#define LOG_ALWAYS_FATAL_IF(cond, ...) ((void)0)
#endif

#ifndef IF_ALOG
#define IF_ALOG(priority, tag) if (false)
#endif
