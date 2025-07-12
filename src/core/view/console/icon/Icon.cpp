#include "view/icon/Icon.h"

size_t icon_width(const Icon& icon) {
    return icon.empty() ? 0 : icon[0].size();
}

size_t icon_height(const Icon& icon) {
    return icon.size();
}


