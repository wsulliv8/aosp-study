#pragma once

#include <utils/RefBase.h>
#include <utils/StrongPointer.h>

namespace android {
namespace hardware {
namespace graphics {
namespace bufferqueue {
namespace V2_0 {

class IProducerListener : public virtual RefBase {
public:
    virtual ~IProducerListener() = default;
    virtual void onBufferReleased() {}
};

} // namespace V2_0
} // namespace bufferqueue
} // namespace graphics
} // namespace hardware
} // namespace android
