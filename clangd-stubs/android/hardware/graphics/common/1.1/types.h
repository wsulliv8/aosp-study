#pragma once

#include <cstdint>

namespace android {
namespace hardware {
namespace graphics {
namespace common {
namespace V1_1 {

enum class RenderIntent : int32_t {
    COLORIMETRIC = 0,
    ENHANCE = 1,
    TONE_MAP_COLORIMETRIC = 2,
    TONE_MAP_ENHANCE = 3,
};

enum class ColorMode : int32_t {
    NATIVE = 0,
    STANDARD_BT601_625 = 1,
    STANDARD_BT601_525 = 2,
    STANDARD_BT709 = 3,
    DCI_P3 = 4,
    SRGB = 5,
    ADOBE_RGB = 6,
    DISPLAY_P3 = 7,
};

enum class Dataspace : int32_t {
    UNKNOWN = 0,
    ARBITRARY = 1,
    STANDARD_SHIFT = 16,
    TRANSFER_SHIFT = 22,
    RANGE_SHIFT = 27,
    STANDARD_BT709 = 1 << 16,
    TRANSFER_SRGB = 2 << 22,
    RANGE_FULL = 1 << 27,
    V0_SRGB_LINEAR = 0x200,
    V0_SCRGB_LINEAR = 0x4010000,
    V0_SRGB = 0x201,
    V0_SCRGB = 0x4010001,
    DISPLAY_BT2020 = (1 << 16) | (2 << 22) | (1 << 27),
};

enum class PixelFormat : int32_t {
    RGBA_8888 = 1,
    RGBX_8888 = 2,
    RGB_888 = 3,
    RGB_565 = 4,
    BGRA_8888 = 5,
    RGBA_5551 = 6,
    RGBA_4444 = 7,
    DEPTH_16 = 0x30,
    DEPTH_24 = 0x31,
    DEPTH_24_STENCIL_8 = 0x32,
    DEPTH_32F = 0x33,
    DEPTH_32F_STENCIL_8 = 0x34,
    STENCIL_8 = 0x35,
};

enum class BufferUsage : uint64_t {
    CPU_READ_NEVER = 0,
    CPU_READ_RARELY = 2,
    CPU_READ_OFTEN = 3,
    CPU_WRITE_NEVER = 0,
    CPU_WRITE_RARELY = 32,
    CPU_WRITE_OFTEN = 48,
    GPU_TEXTURE = 256,
    GPU_RENDER_TARGET = 512,
    COMPOSER_OVERLAY = 2048,
    COMPOSER_CLIENT_TARGET = 4096,
    PROTECTED = 16384,
    CAMERA_OUTPUT = 131072,
    CAMERA_INPUT = 262144,
    VIDEO_ENCODER = 65536,
    VIDEO_DECODER = 4194304,
    SENSOR_DIRECT_DATA = 8388608,
    GPU_DATA_BUFFER = 16777216,
    VENDOR_MASK = 0xf000000000000000ULL,
};

}  // namespace V1_1
}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
