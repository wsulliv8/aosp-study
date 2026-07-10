#pragma once

namespace android {

template <typename T>
struct trait_trivial_move {
    enum { value = false };
};

} // namespace android
