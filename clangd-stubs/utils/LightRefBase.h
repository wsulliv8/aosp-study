#pragma once

#include <stdint.h>
#include <sys/types.h>

namespace android {

template <typename T>
class LightRefBase {
public:
    inline LightRefBase() : mCount(0) {}
    inline void incStrong(__attribute__((unused)) const void* id) const {
        __sync_fetch_and_add(&mCount, 1);
    }
    inline void decStrong(__attribute__((unused)) const void* id) const {
        if (__sync_fetch_and_sub(&mCount, 1) == 1) {
            delete static_cast<const T*>(this);
        }
    }
    inline int32_t getStrongCount() const { return mCount; }

protected:
    inline ~LightRefBase() {}

private:
    mutable volatile int32_t mCount;
};

} // namespace android
