#pragma once

#include <cstdint>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum class BlendMode : int32_t {
    INVALID = 0,
    NONE = 1,
    PREMULTIPLIED = 2,
    COVERAGE = 3,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
