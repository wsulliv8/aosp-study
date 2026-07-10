#pragma once

#include <cstdint>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum class DisplayHotplugEvent : int32_t {
    CONNECTED = 0,
    DISCONNECTED = 1,
    ERROR_UNKNOWN = -1,
    ERROR_INCOMPATIBLE_CABLE = -2,
    ERROR_TOO_MANY_DISPLAYS = -3,
    ERROR_LINK_UNSTABLE = -4,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
