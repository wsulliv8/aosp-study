#pragma once

#ifndef ATRACE_TAG
#define ATRACE_TAG 0
#endif

#define ATRACE_ENABLED() (false)
#define ATRACE_CALL() ((void)0)
#define ATRACE_NAME(name) ((void)0)
#define ATRACE_INT(name, value) ((void)0)
#define ATRACE_INT64(name, value) ((void)0)
#define ATRACE_BEGIN(name) ((void)0)
#define ATRACE_END() ((void)0)
