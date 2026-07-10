#pragma once

#include <utils/Errors.h>
#include <utils/RefBase.h>
#include <utils/StrongPointer.h>

namespace android {

class Thread : virtual public RefBase {
public:
    virtual bool threadLoop() = 0;
    status_t run(const char* name = nullptr, int32_t priority = 0, size_t stack = 0);
    status_t requestExit();
    status_t requestExitAndWait();
};

} // namespace android

#include <stddef.h>
#include <stdint.h>
