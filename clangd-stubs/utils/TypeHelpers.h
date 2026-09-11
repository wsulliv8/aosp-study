#pragma once

namespace android {

template <typename T>
struct trait_trivial_ctor {
    enum { value = false };
};
template <typename T>
struct trait_trivial_dtor {
    enum { value = false };
};
template <typename T>
struct trait_trivial_copy {
    enum { value = false };
};
template <typename T>
struct trait_trivial_move {
    enum { value = false };
};

#define ANDROID_TRIVIAL_COPY_TRAIT(T)
#define ANDROID_TRIVIAL_MOVE_TRAIT(T)
#define ANDROID_TRIVIAL_DTOR_TRAIT(T)
#define ANDROID_BASIC_TYPES_TRAITS(T)

} // namespace android
