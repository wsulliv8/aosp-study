#pragma once

#include <cstdint>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum class AlphaInterpretation : int32_t {
    COVERAGE = 0,
    MASK = 1,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
