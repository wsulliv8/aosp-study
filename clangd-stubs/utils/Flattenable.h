#pragma once

#include <stddef.h>
#include <stdint.h>
#include <utils/Errors.h>

namespace android {

template <typename T>
class Flattenable {
public:
    size_t getFlattenedSize() const { return static_cast<const T*>(this)->getFlattenedSize(); }
    size_t getFdCount() const { return static_cast<const T*>(this)->getFdCount(); }
    status_t flatten(void*& buffer, size_t& size, int*& fds, size_t& count) const {
        return static_cast<const T*>(this)->flatten(buffer, size, fds, count);
    }
    status_t unflatten(void const*& buffer, size_t& size, int const*& fds, size_t& count) {
        return static_cast<T*>(this)->unflatten(buffer, size, fds, count);
    }
};

template <typename T>
class LightFlattenable {
public:
    bool isFixedSize() const { return static_cast<const T*>(this)->isFixedSize(); }
    size_t getFlattenedSize() const { return static_cast<const T*>(this)->getFlattenedSize(); }
    status_t flatten(void* buffer, size_t size) const {
        return static_cast<const T*>(this)->flatten(buffer, size);
    }
    status_t unflatten(void const* buffer, size_t size) {
        return static_cast<T*>(this)->unflatten(buffer, size);
    }
};

template <typename T>
class LightFlattenablePod : public LightFlattenable<T> {
public:
    bool isFixedSize() const { return true; }
    size_t getFlattenedSize() const { return sizeof(T); }
    status_t flatten(void* buffer, size_t size) const {
        if (size < sizeof(T)) return NO_MEMORY;
        *reinterpret_cast<T*>(buffer) = *static_cast<const T*>(this);
        return OK;
    }
    status_t unflatten(void const* buffer, size_t size) {
        if (size < sizeof(T)) return NO_MEMORY;
        *static_cast<T*>(this) = *reinterpret_cast<const T*>(buffer);
        return OK;
    }
};

} // namespace android
