#include "model/object/Viewable.h"

size_t Viewable::icon_width() const {
	return icon_.empty() ? 0 : icon_[0].size();
}

size_t Viewable::icon_height() const {
	return icon_.size();
}

const Icon& Viewable::getIcon() const {
	return icon_;
}
void Viewable::setIcon(const Icon& icon) {
	icon_ = icon;
}