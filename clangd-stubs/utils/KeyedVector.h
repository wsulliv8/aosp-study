#pragma once

#include <utils/Vector.h>

namespace android {

template <class KEY, class VALUE>
class KeyedVector : public Vector<VALUE> {
public:
    ssize_t indexOfKey(const KEY& key) const;
    const VALUE& valueFor(const KEY& key) const;
    VALUE& editValueFor(const KEY& key);
    status_t add(const KEY& key, const VALUE& value);
    status_t replaceValueFor(const KEY& key, const VALUE& value);
};

} // namespace android

#include <sys/types.h>
