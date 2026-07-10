#pragma once

namespace android {

class Mutex {
public:
    Mutex() = default;
    void lock();
    void unlock();
    bool tryLock();

    class Autolock {
    public:
        explicit Autolock(Mutex& mutex);
        ~Autolock();
    private:
        Mutex& mMutex;
    };
};

} // namespace android
