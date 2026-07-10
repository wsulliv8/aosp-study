#pragma once

#define DISALLOW_COPY_AND_ASSIGN(TypeName)

#define FALLTHROUGH_INTENDED [[fallthrough]]

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define CC_LIKELY(x) LIKELY(x)
#define CC_UNLIKELY(x) UNLIKELY(x)
