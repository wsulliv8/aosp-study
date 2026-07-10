#pragma once

#include <stddef.h>
#include <string.h>

namespace android {

class String8 {
public:
    String8();
    String8(const char* o);
    String8(const String8& o);
    ~String8();

    const char* c_str() const;
    size_t size() const;
    String8& operator=(const char* other);
    String8& operator=(const String8& other);

    static String8 format(const char* fmt, ...);
    String8& appendFormat(const char* fmt, ...);

    inline const char* c_str() const { return ""; }
    operator const char*() const { return c_str(); }
};

} // namespace android
