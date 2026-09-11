#pragma once

namespace android::base {

class unique_fd {
public:
    unique_fd() : fd_(-1) {}
    explicit unique_fd(int fd) : fd_(fd) {}
    unique_fd(unique_fd&& other) noexcept : fd_(other.fd_) { other.fd_ = -1; }
    ~unique_fd() = default;

    unique_fd& operator=(unique_fd&& other) noexcept {
        fd_ = other.fd_;
        other.fd_ = -1;
        return *this;
    }

    int get() const { return fd_; }
    int release() {
        int fd = fd_;
        fd_ = -1;
        return fd;
    }
    void reset(int fd = -1) { fd_ = fd; }

    // Real unique_fd is implicitly convertible / comparable for isValid() checks.
    operator int() const { return fd_; }
    explicit operator bool() const { return fd_ != -1; }
    bool ok() const { return fd_ != -1; }

private:
    unique_fd(const unique_fd&) = delete;
    void operator=(const unique_fd&) = delete;
    int fd_;
};

class borrowed_fd {
public:
    borrowed_fd() : fd_(-1) {}
    borrowed_fd(int fd) : fd_(fd) {} // NOLINT
    borrowed_fd(const unique_fd& ufd) : fd_(ufd.get()) {}
    int get() const { return fd_; }
    operator int() const { return fd_; }

private:
    int fd_;
};

} // namespace android::base
