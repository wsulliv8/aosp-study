#pragma once

#include <cstdint>

namespace aidl {
namespace android {
namespace hardware {
namespace graphics {
namespace common {

enum class BufferUsage : int32_t {
    CPU_READ_NEVER = 0,
    CPU_READ_RARELY = 2,
    CPU_READ_OFTEN = 3,
};

}  // namespace common
}  // namespace graphics
}  // namespace hardware
}  // namespace android
}  // namespace aidl
