#pragma once

// Minimal sp/wp for IDE navigation. Do not include RefBase.h here (RefBase includes us).

namespace android {

template <typename T>
class sp {
public:
    sp() : m_ptr(nullptr) {}
    sp(T* other) : m_ptr(other) {}
    sp(const sp<T>& other) : m_ptr(other.m_ptr) {}
    sp(sp<T>&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
    template <typename U>
    sp(const sp<U>& other) : m_ptr(other.get()) {}
    ~sp() = default;

    sp& operator=(T* other) {
        m_ptr = other;
        return *this;
    }
    sp& operator=(const sp<T>& other) {
        m_ptr = other.m_ptr;
        return *this;
    }
    sp& operator=(sp<T>&& other) noexcept {
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
        return *this;
    }

    T* get() const { return m_ptr; }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    explicit operator bool() const { return m_ptr != nullptr; }
    bool operator==(const sp<T>& o) const { return m_ptr == o.m_ptr; }
    bool operator!=(const sp<T>& o) const { return m_ptr != o.m_ptr; }
    bool operator==(const T* o) const { return m_ptr == o; }
    bool operator!=(const T* o) const { return m_ptr != o; }

    void clear() { m_ptr = nullptr; }

    template <typename U>
    static sp<U> cast(const sp<T>& other) {
        return sp<U>(static_cast<U*>(other.get()));
    }

    template <typename... Args>
    static sp<T> make(Args&&... args) {
        return sp<T>(new T(static_cast<Args&&>(args)...));
    }

    // Used widely in binder headers (does not bump refcount in real libutils;
    // for IDE stubs, same as constructing from raw pointer).
    static sp<T> fromExisting(T* other) { return sp<T>(other); }

private:
    T* m_ptr;
};

template <typename T>
class wp {
public:
    wp() : m_ptr(nullptr) {}
    wp(T* other) : m_ptr(other) {}
    wp(const wp<T>& other) : m_ptr(other.m_ptr) {}
    wp(const sp<T>& other) : m_ptr(other.get()) {}
    ~wp() = default;

    wp& operator=(T* other) {
        m_ptr = other;
        return *this;
    }
    wp& operator=(const wp<T>& other) {
        m_ptr = other.m_ptr;
        return *this;
    }
    wp& operator=(const sp<T>& other) {
        m_ptr = other.get();
        return *this;
    }

    sp<T> promote() const { return sp<T>(m_ptr); }
    void clear() { m_ptr = nullptr; }

private:
    T* m_ptr;
};

} // namespace android
