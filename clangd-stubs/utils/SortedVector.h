#pragma once

#include <utils/Vector.h>

namespace android {

template <class TYPE>
class SortedVector : public Vector<TYPE> {
public:
    ssize_t indexOf(const TYPE& item) const;
    status_t add(const TYPE& item);
};

} // namespace android

#include <sys/types.h>
