#pragma once

#include <stdint.h>

typedef int64_t nsecs_t;

enum {
    SYSTEM_TIME_REALTIME = 0,
    SYSTEM_TIME_MONOTONIC = 1,
    SYSTEM_TIME_PROCESS = 2,
    SYSTEM_TIME_THREAD = 3,
    SYSTEM_TIME_BOOTTIME = 4,
};

static constexpr nsecs_t s2ns(nsecs_t sec) { return sec * 1000000000LL; }
static constexpr nsecs_t ms2ns(nsecs_t ms) { return ms * 1000000LL; }
static constexpr nsecs_t us2ns(nsecs_t us) { return us * 1000LL; }
static constexpr nsecs_t ns2ms(nsecs_t ns) { return ns / 1000000LL; }

inline nsecs_t systemTime(int /*clock*/ = SYSTEM_TIME_MONOTONIC) { return 0; }
