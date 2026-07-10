#pragma once

#include <cstdint>
#include <vector>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

struct PlaneLayoutComponent {
    int64_t typeInComponent = 0;
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

struct XyColor {
    float x = 0;
    float y = 0;
};

struct Cta861_3 {
    float maxContentLightLevel = 0;
    float maxFrameAverageLightLevel = 0;
};

struct Smpte2086 {
    XyColor displayPrimaryRed;
    XyColor displayPrimaryGreen;
    XyColor displayPrimaryBlue;
    XyColor whitePoint;
    float maxLuminance = 0;
    float minLuminance = 0;
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
