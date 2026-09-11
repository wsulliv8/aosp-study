#pragma once

#include <cstdint>

namespace android::gui {

enum class FrameEvent : int32_t {
    UNKNOWN = 0,
    POSTED = 1,
    REQUESTED_PRESENT = 2,
    LATCH = 3,
    ACQUIRE = 4,
    FIRST_REFRESH_START = 5,
    LAST_REFRESH_START = 6,
    GPU_COMPOSITION_DONE = 7,
    DISPLAY_PRESENT = 8,
    DEQUEUE_READY = 9,
    RELEASE = 10,
    EVENT_COUNT = 11,
};

} // namespace android::gui
