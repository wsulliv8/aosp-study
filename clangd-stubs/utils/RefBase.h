#pragma once

namespace android {

class RefBase {
public:
    void incStrong(const void* id) const;
    void decStrong(const void* id) const;
    void forceIncStrong(const void* id) const;

    class weakref_type;

protected:
    RefBase() = default;
    virtual ~RefBase() = default;
};

} // namespace android

// Real libutils RefBase.h pulls in StrongPointer so #include <utils/RefBase.h>
// provides sp<> / wp<> (needed by binder/IBinder.h etc.).
#include <utils/StrongPointer.h>
#include <utils/LightRefBase.h>
