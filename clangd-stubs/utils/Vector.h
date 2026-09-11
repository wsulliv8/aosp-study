#pragma once

#include <cstddef>
#include <utils/Errors.h>

namespace android {

template <class TYPE>
class Vector {
public:
    using iterator = TYPE*;
    using const_iterator = const TYPE*;

    Vector() = default;
    size_t size() const { return mSize; }
    bool isEmpty() const { return mSize == 0; }
    bool empty() const { return mSize == 0; }
    TYPE& operator[](size_t index) { return mItems[index]; }
    const TYPE& operator[](size_t index) const { return mItems[index]; }
    TYPE& editItemAt(size_t index) { return mItems[index]; }
    const TYPE& itemAt(size_t index) const { return mItems[index]; }
    TYPE& top() { return mItems[mSize - 1]; }
    const TYPE& top() const { return mItems[mSize - 1]; }
    iterator begin() { return mItems; }
    iterator end() { return mItems + mSize; }
    const_iterator begin() const { return mItems; }
    const_iterator end() const { return mItems + mSize; }
    status_t add(const TYPE& /*item*/) { return OK; }
    void push(const TYPE& /*item*/) {}
    void push_back(const TYPE& /*item*/) {}
    void pop() {}
    void pop_back() {}
    void clear() { mSize = 0; }
    iterator erase(iterator /*pos*/) { return mItems; }
    iterator erase(iterator /*first*/, iterator /*last*/) { return mItems; }
    ssize_t removeAt(size_t /*index*/) { return 0; }
    ssize_t insertAt(const TYPE& /*item*/, size_t /*index*/) { return 0; }

private:
    TYPE* mItems = nullptr;
    size_t mSize = 0;
};

} // namespace android
