#pragma once

#include <memory>

class IView {
public:
	using Ptr = std::unique_ptr<IView>;

	virtual void update() = 0;
	virtual void render() const = 0;
};
