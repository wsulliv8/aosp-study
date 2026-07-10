#pragma once

#include <utils/RefBase.h>
#include <utils/StrongPointer.h>

namespace android {

class Looper : public RefBase {
public:
    static sp<Looper> prepare(int opts = 0);
    static sp<Looper> getForThread();
    int pollAll(int timeoutMillis, int* outFd, int* outEvents, void** outData);
    int pollOnce(int timeoutMillis, int* outFd, int* outEvents, void** outData);
    void wake();
};

} // namespace android
