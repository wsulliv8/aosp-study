#pragma once

#include <utils/RefBase.h>

namespace android::gui {

class BnJankListener : public virtual RefBase {
public:
    virtual ~BnJankListener() = default;
};

} // namespace android::gui
