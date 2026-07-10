#pragma once

#include <cstdint>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum class ChromaSiting : int32_t {
    NONE = 0,
    UNKNOWN = 1,
    SITED_INTERSTITIAL = 2,
    COSITED_HORIZONTAL = 3,
    COSITED_VERTICAL = 4,
    COSITED_BOTH = 5,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
