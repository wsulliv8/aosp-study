#pragma once

namespace android::base {

class unique_fd {
public:
    unique_fd() : fd_(-1) {}
    explicit unique_fd(int fd) : fd_(fd) {}
    ~unique_fd();

    int get() const { return fd_; }
    int release();
    void reset(int fd = -1);

private:
    int fd_;
};

class borrowed_fd {
public:
    explicit borrowed_fd(int fd) : fd_(fd) {}
    int get() const { return fd_; }

private:
    int fd_;
};

} // namespace android::base
