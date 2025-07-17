#pragma once

#include <memory>

// ***************************************************************************/

namespace GameLib::Core {

	class Event {
	public:
		using S_Ptr = std::shared_ptr<Event>;

		virtual ~Event() = default;
	};
	

}


// template <typename Derived>
// class BaseEvent : public IEvent {
// public:
// 	using Ptr = std::shared_ptr<Derived>;
// 	static Ptr create() {
// 		return std::make_shared<Derived>();
// 	}

// protected:
// 	BaseEvent() {}
// 	virtual ~BaseEvent() = default;

// public:
// 	const ClientSession::Ptr sender_;
// };

// template<typename Derived>
// concept IsEvent = std::derived_from<Derived, BaseEvent<Derived>>;

