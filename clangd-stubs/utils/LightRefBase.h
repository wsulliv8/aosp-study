#pragma once

#include <utils/RefBase.h>

namespace android {

template <typename T>
class LightRefBase : public virtual RefBase {
public:
    void incStrong(const void* id) const { RefBase::incStrong(id); }
    void decStrong(const void* id) const { RefBase::decStrong(id); }

protected:
    virtual ~LightRefBase() = default;
};

} // namespace android
