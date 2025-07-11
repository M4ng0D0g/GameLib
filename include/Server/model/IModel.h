#pragma once

#include "BaseGameObject.h"
#include <memory>
#include <unordered_map>

class IModel {
public:
	using Ptr = std::unique_ptr<IModel>;

	virtual std::unordered_map<size_t, BaseGameObject::Ptr>& getObjs() = 0;
};