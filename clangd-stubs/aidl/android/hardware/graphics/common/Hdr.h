#pragma once

#include <cstdint>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum class Hdr : int32_t {
    INVALID = 0,
    DOLBY_VISION = 1,
    HDR10 = 2,
    HLG = 3,
    HDR10_PLUS = 4,
    DOLBY_VISION_4K30 = 5,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
