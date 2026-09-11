#pragma once

#include <stdint.h>

namespace android {

class String16 {
public:
    String16() = default;
    String16(const char* /*o*/) {}
    String16(const char16_t* /*o*/) {}
    String16(const String16& /*o*/) = default;
    ~String16() = default;

    String16& operator=(const String16& /*o*/) = default;
    bool operator==(const String16& /*o*/) const { return true; }
    bool operator!=(const String16& /*o*/) const { return false; }

    const char16_t* string() const { return u""; }
    size_t size() const { return 0; }
};

} // namespace android
