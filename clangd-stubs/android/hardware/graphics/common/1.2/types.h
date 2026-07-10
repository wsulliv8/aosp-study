#pragma once

#include <android/hardware/graphics/common/1.1/types.h>

namespace android {
namespace hardware {
namespace graphics {
namespace common {
namespace V1_2 {

using V1_1::BufferUsage;
using V1_1::ColorMode;
using V1_1::Dataspace;
using V1_1::PixelFormat;
using V1_1::RenderIntent;

enum class Hdr : int32_t {
    DOLBY_VISION = 1,
    HDR10 = 2,
    HLG = 3,
    HDR10_PLUS = 4,
};

}  // namespace V1_2
}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
