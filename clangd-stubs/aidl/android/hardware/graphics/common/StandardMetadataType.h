#pragma once

#include <cstdint>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum class StandardMetadataType : int32_t {
    INVALID = 0,
    BUFFER_ID = 1,
    NAME = 2,
    WIDTH = 3,
    HEIGHT = 4,
    LAYER_COUNT = 5,
    PIXEL_FORMAT_REQUESTED = 6,
    PIXEL_FORMAT_FOURCC = 7,
    PIXEL_FORMAT_MODIFIER = 8,
    USAGE = 9,
    ALLOCATION_SIZE = 10,
    PROTECTED_CONTENT = 11,
    COMPRESSION = 12,
    INTERLACED = 13,
    CHROMA_SITING = 14,
    PLANE_LAYOUTS = 15,
    CROP = 16,
    DATASPACE = 17,
    BLEND_MODE = 18,
    SMPTE2086 = 19,
    CTA861_3 = 20,
    SMPTE2094_40 = 21,
    SMPTE2094_10 = 22,
    STRIDE = 23,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
