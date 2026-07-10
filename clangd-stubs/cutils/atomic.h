#pragma once

#include <stdint.h>

static inline int32_t android_atomic_inc(volatile int32_t* addr) {
    return ++(*const_cast<int32_t*>(addr));
}

static inline int32_t android_atomic_dec(volatile int32_t* addr) {
    return --(*const_cast<int32_t*>(addr));
}

static inline int32_t android_atomic_acquire_load(volatile const int32_t* addr) {
    return *addr;
}

static inline void android_atomic_release_store(int32_t value, volatile int32_t* addr) {
    *const_cast<int32_t*>(addr) = value;
}
