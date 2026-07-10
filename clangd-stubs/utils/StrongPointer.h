#pragma once

#include <utils/RefBase.h>

namespace android {

template <typename T>
class sp {
public:
    sp() : m_ptr(nullptr) {}
    sp(T* other);
    sp(const sp<T>& other);
    sp(sp<T>&& other) noexcept;
    ~sp();

    sp& operator=(T* other);
    sp& operator=(const sp<T>& other);
    sp& operator=(sp<T>&& other) noexcept;

    T* get() const { return m_ptr; }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    explicit operator bool() const { return m_ptr != nullptr; }

    template <typename U>
    static sp<U> cast(const sp<T>& other);

    template <typename... Args>
    static sp<T> make(Args&&... args);

private:
    T* m_ptr;
};

template <typename T>
class wp {
public:
    wp() : m_ptr(nullptr) {}
    wp(T* other);
    wp(const wp<T>& other);
    wp(const sp<T>& other);
    ~wp();

    wp& operator=(T* other);
    wp& operator=(const wp<T>& other);
    wp& operator=(const sp<T>& other);

    sp<T> promote() const;

private:
    T* m_ptr;
};

} // namespace android
