#pragma once

#include <cstddef>

namespace android {

template <class TYPE>
class Vector {
public:
    using iterator = TYPE*;
    using const_iterator = const TYPE*;

    Vector() = default;
    size_t size() const { return mSize; }
    bool isEmpty() const { return mSize == 0; }
    TYPE& operator[](size_t index) { return mItems[index]; }
    const TYPE& operator[](size_t index) const { return mItems[index]; }
    TYPE& editItemAt(size_t index) { return mItems[index]; }
    const TYPE& itemAt(size_t index) const { return mItems[index]; }
    iterator begin() { return mItems; }
    iterator end() { return mItems + mSize; }
    const_iterator begin() const { return mItems; }
    const_iterator end() const { return mItems + mSize; }
    status_t add(const TYPE& item);
    void clear();

private:
    TYPE* mItems = nullptr;
    size_t mSize = 0;
};

} // namespace android
