#pragma once

#include <cstdint>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum class ColorTransform : int32_t {
    IDENTITY = 0,
    ARBITRARY_MATRIX = 1,
    VALUE_INVERSE = 2,
    GRAYSCALE = 3,
    CORRECT_PROTANOPIA = 4,
    CORRECT_DEUTERANOPIA = 5,
    CORRECT_TRITANOPIA = 6,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
