#pragma once

#include <cstdint>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum class Dataspace : int32_t {
    STANDARD_SHIFT = 16,
    TRANSFER_SHIFT = 22,
    RANGE_SHIFT = 27,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
