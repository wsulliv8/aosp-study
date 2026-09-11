#pragma once

#ifndef ATRACE_TAG
#define ATRACE_TAG 0
#endif

#define ATRACE_TAG_ALWAYS 0
#define ATRACE_TAG_GRAPHICS (1 << 1)
#define ATRACE_TAG_HAL (1 << 11)
#define ATRACE_TAG_APP (1 << 12)

#define ATRACE_ENABLED() (false)
#define ATRACE_CALL() ((void)0)
#define ATRACE_NAME(name) ((void)0)
#define ATRACE_INT(name, value) ((void)0)
#define ATRACE_INT64(name, value) ((void)0)
#define ATRACE_BEGIN(name) ((void)0)
#define ATRACE_END() ((void)0)
#define ATRACE_INSTANT(name) ((void)0)
#define ATRACE_FORMAT(...) ((void)0)
#define ATRACE_FORMAT_INSTANT(...) ((void)0)

namespace android {

class ScopedTrace {
public:
    explicit ScopedTrace(uint64_t /*tag*/, const char* /*name*/) {}
    ~ScopedTrace() = default;
};

} // namespace android
