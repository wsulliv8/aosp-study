#pragma once

#include <utility>

namespace android::base {

template <typename T, typename E>
class expected {
public:
    expected(T value) : mHasValue(true), mValue(std::move(value)) {}
    expected(E error) : mHasValue(false), mError(std::move(error)) {}

    bool has_value() const { return mHasValue; }
    explicit operator bool() const { return mHasValue; }
    T& value() { return mValue; }
    const T& value() const { return mValue; }
    E& error() { return mError; }
    const E& error() const { return mError; }

private:
    bool mHasValue;
    T mValue{};
    E mError{};
};

} // namespace android::base
