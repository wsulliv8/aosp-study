#pragma once

#include <cutils/native_handle.h>

namespace android {

class NativeHandle {
public:
    NativeHandle();
    explicit NativeHandle(const native_handle* handle);
    ~NativeHandle();

    const native_handle* handle() const;
    native_handle* handle();

private:
    native_handle* mHandle;
};

} // namespace android
