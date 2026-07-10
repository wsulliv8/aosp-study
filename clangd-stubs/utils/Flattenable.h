#pragma once

#include <utils/Errors.h>
#include <stddef.h>
#include <stdint.h>

namespace android {

class Flattenable {
public:
    virtual ~Flattenable() = default;
    virtual size_t getFlattenedSize() const = 0;
    virtual size_t getFdCount() const = 0;
    virtual status_t flatten(void* buffer, size_t size, int* fds, size_t count) const = 0;
    virtual status_t unflatten(void const* buffer, size_t size, int* fds, size_t count) = 0;
};

} // namespace android
