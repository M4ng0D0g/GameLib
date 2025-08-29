#pragma once

#include <memory>
#include <type_traits>
#include <iostream>


// ***************************************************************************/

namespace gamelib::event {

	class Event : public std::enable_shared_from_this<Event> {
	public:
		virtual ~Event() = default;

		// --------------------------------------------------------------------------------

		template <typename T>
		std::shared_ptr<T> castDerived() {
			auto casted = std::dynamic_pointer_cast<T>(this->shared_from_this());
			if (!casted) {
				// log warning
				return nullptr;
			}
			else return casted;
		} 

	};
	
}

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


// };


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

/*
#pragma once

#include "BaseEvent.h"
#include <mutex>
#include <vector>
#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <typeindex>

class EventBus {
public:
	using Token = size_t; //考慮 enum class 強型別

	template<IsEvent Derived>
	using Callback = std::function<void(const typename Derived::Ptr&)>; //保護事件不受修改

private:
	std::mutex mutex_;
	Token nextToken_ = 1;

	struct ICallbackWrapper {
		// 定義 Ptr
		using Ptr = std::shared_ptr<ICallbackWrapper>;

		virtual ~ICallbackWrapper() = default;
		virtual void call(IEvent::Ptr) = 0;
	};

	template<IsEvent Derived>
	struct CallbackWrapper : ICallbackWrapper {
		Callback<Derived> cb_;
		CallbackWrapper(Callback<Derived> cb) : cb_(std::move(cb)) {}
		
		// 定義 Ptr 及 create (為了統一介面)
		using Ptr = std::shared_ptr<CallbackWrapper>;
		static Ptr create(Callback<Derived> cb) {
			return std::make_shared<CallbackWrapper<Derived>>(std::move(cb));
		}

		// 匹配到正確型態後才將事件轉型
		void call(IEvent::Ptr base) override {
			if (auto derived = std::dynamic_pointer_cast<Derived>(base)) cb(derived);
		}
	};

	// 儲存每個事件型別對應的 Token 與處理器
	std::unordered_map<std::type_index, std::unordered_map<Token, ICallbackWrapper::Ptr>> subscribers_;

public:
	template<IsEvent Derived>
	Token subscribe(Callback<Derived> callback) {
		std::lock_guard<std::mutex> lock(mutex_);

		Token token = nextToken_++;
		auto& map = subscribers_[std::type_index(typeid(Derived))];
		map[token] = CallbackWrapper<Derived>::create(std::move(callback));

		return token;
	}

	template<IsEvent Derived>
	bool unsubscribe(Token token) {
		std::lock_guard<std::mutex> lock(mutex_);

		auto it = subscribers_.find(std::type_index(typeid(Derived)));
		if (it != subscribers_.end()) {
			auto& map = it->second;
			return map.erase(token) > 0;
		}
		return false;
	}

	void dispatch(const IEvent::Ptr& event) {
		std::lock_guard<std::mutex> lock(mutex_);

		// event 需要有虛擬函式(虛擬解構子)
		auto it = subscribers_.find(std::type_index(typeid(*event)));
		if (it != subscribers_.end()) {
			for (auto& [_, wrapper] : it->second) wrapper->call(event);
		}
	}
};

*/