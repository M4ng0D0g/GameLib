#pragma once

#include <memory>
#include <type_traits>
#include <iostream>


// ***************************************************************************/

namespace GameLib::Core {

	// class BaseEvent : public std::enable_shared_from_this<BaseEvent> {
	// public:
	// 	using S_Ptr = std::shared_ptr<BaseEvent>;
	// 	virtual ~BaseEvent() = default;
	// };

	// // 模板事件
	// template <typename T>
	// class Event : public BaseEvent {
	// 	static_assert(std::is_base_of<BaseEvent, T>::value, "T 必須繼承自 BaseEvent");

	// public:
	// 	using S_Ptr = std::shared_ptr<T>;
	// 	virtual ~Event() = default;

	// 	S_Ptr castDerived() {
	// 		return std::dynamic_pointer_cast<T>(this->shared_from_this());
	// 	} 
	// };

	class Event {
	public:
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

