#pragma once

namespace android {

class RefBase {
public:
    void incStrong(const void* id) const;
    void decStrong(const void* id) const;
    void forceIncStrong(const void* id) const;

protected:
    virtual ~RefBase() = default;
};

} // namespace android
