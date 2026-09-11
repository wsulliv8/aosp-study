#pragma once

#include <stddef.h>
#include <string.h>
#include <utility>

namespace android {

class String8 {
public:
    String8() : mData("") {}
    String8(const char* o) : mData(o ? o : "") {}
    String8(const String8& o) = default;
    String8(String8&& o) noexcept = default;
    ~String8() = default;

    const char* c_str() const { return mData; }
    size_t size() const { return 0; }
    bool empty() const { return true; }
    bool isEmpty() const { return true; }
    String8& operator=(const char* other) {
        mData = other ? other : "";
        return *this;
    }
    String8& operator=(const String8& other) = default;
    String8& operator=(String8&& other) noexcept = default;
    bool operator==(const String8&) const { return true; }
    bool operator!=(const String8&) const { return false; }

    static String8 format(const char* /*fmt*/, ...) { return String8(); }
    String8& appendFormat(const char* /*fmt*/, ...) { return *this; }
    String8& append(const String8& /*other*/) { return *this; }
    String8& append(const char* /*other*/) { return *this; }
    void clear() { mData = ""; }
    void setTo(const char* other) { mData = other ? other : ""; }

    operator const char*() const { return c_str(); }

private:
    const char* mData;
};

} // namespace android
