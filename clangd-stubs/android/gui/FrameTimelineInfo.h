#pragma once

#include <cstdint>

namespace android::gui {

struct FrameTimelineInfo {
    int64_t vsyncId = -1;
    int32_t inputEventId = 0;
    int64_t startTimeNanos = 0;
    bool useForRefreshRateSelection = false;
    static constexpr int64_t INVALID_VSYNC_ID = -1;
};

} // namespace android::gui
