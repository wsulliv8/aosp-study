#pragma once

#include <cutils/native_handle.h>
#include <utils/StrongPointer.h>

namespace android {

class NativeHandle : public LightRefBase<NativeHandle> {
public:
    NativeHandle();
    explicit NativeHandle(const native_handle_t* handle, bool ownsHandle = true);
    ~NativeHandle();

    static sp<NativeHandle> create(native_handle_t* handle, bool ownHandle);
    static sp<NativeHandle> create(const native_handle_t* handle, bool ownHandle);

    const native_handle_t* handle() const { return mHandle; }
    native_handle_t* handle() { return mHandle; }

private:
    native_handle_t* mHandle = nullptr;
    bool mOwnsHandle = false;
};

} // namespace android
