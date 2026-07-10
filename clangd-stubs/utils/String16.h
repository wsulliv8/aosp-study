#pragma once

#include <utils/String8.h>

namespace android {

class String16 {
public:
    String16();
    String16(const char* o);
    String16(const String16& o);
    ~String16();
};

} // namespace android
