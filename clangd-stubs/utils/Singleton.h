#pragma once

namespace android {

template <typename TYPE>
class Singleton {
public:
    static TYPE& getInstance();
};

} // namespace android
