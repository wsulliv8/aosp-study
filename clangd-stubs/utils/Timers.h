#pragma once

#include <stdint.h>

typedef int64_t nsecs_t;

static constexpr nsecs_t s2ns(nsecs_t sec) { return sec * 1000000000; }
static constexpr nsecs_t ms2ns(nsecs_t ms) { return ms * 1000000; }
static constexpr nsecs_t us2ns(nsecs_t us) { return us * 1000; }

nsecs_t systemTime(int clock = 0);
