#pragma once

#include <utils/Errors.h>
#include <utils/Mutex.h>
#include <utils/Timers.h>

namespace android {

class Condition {
public:
    Condition() = default;
    status_t wait(Mutex& mutex);
    status_t waitRelative(Mutex& mutex, nsecs_t reltime);
    void signal();
    void broadcast();
};

} // namespace android
