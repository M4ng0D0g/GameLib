#pragma once

#include <nlohmann/json.hpp>
#include <memory>

// ***************************************************************************/

using json = nlohmann::json;

class IPayload {
public:
	using Ptr = std::shared_ptr<IPayload>;
	virtual ~IPayload() = default;
	virtual json toJson() const = 0;
	virtual Ptr cast() = 0;
};

template <typename Derived>
class BasePayload : public IPayload {
public:
	using Ptr = std::shared_ptr<Derived>;
	static Ptr create() {
		return Ptr(Derived());
	}
	Ptr cast() override {
		return Ptr(this);
	}
};