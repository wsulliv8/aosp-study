#pragma once

#include <cstdint>
#include <vector>

namespace aidl::android::hardware::graphics::common {

struct PlaneLayoutComponent {
    int64_t type = 0;
    int64_t offsetInBits = 0;
    int64_t sizeInBits = 0;
};

struct PlaneLayout {
    std::vector<PlaneLayoutComponent> components;
    int64_t offsetInBytes = 0;
    int64_t sampleIncrementInBits = 0;
    int64_t strideInBytes = 0;
    int64_t widthInSamples = 0;
    int64_t heightInSamples = 0;
    int64_t totalSizeInBytes = 0;
    int64_t horizontalSubsampling = 1;
    int64_t verticalSubsampling = 1;
};

} // namespace aidl::android::hardware::graphics::common
