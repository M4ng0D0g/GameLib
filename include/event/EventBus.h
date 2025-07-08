#pragma once

#include <iostream>
#include <functional>
#include <utility>
#include <vector>
#include <memory>
#include <typeindex>
#include <type_traits>
#include <unordered_map>

template<typename BaseListener, typename BaseEvent>
class EventBus {
	static_assert(std::is_class<BaseListener>::value, "BaseListener 必須是 class");
	static_assert(std::is_class<BaseEvent>::value, "BaseEvent 必須是 class");

public:
	using ListenerPtr = std::shared_ptr<BaseListener>;
	using Handler = std::function<bool(BaseEvent&)>;
	using HandlerPair = std::pair<std::weak_ptr<BaseListener>, Handler>;

private:
	template<typename Event>
	struct Registry {
		static_assert(std::is_base_of<BaseEvent, Event>::value, "Event 必須繼承 BaseEvent");
		static std::vector<HandlerPair> handlers;
	};

public:
	virtual ~EventBus() = default;

	template<typename Event>
	void subscribe(ListenerPtr listener, Handler handler) {
		static_assert(std::is_base_of<BaseEvent, Event>::value, "Event 必須繼承 BaseEvent");
		Registry<Event>::handlers.emplace_back(listener, std::move(handler));
	}

	template<typename Event>
	void unsubscribe(ListenerPtr listener) {
		static_assert(std::is_base_of<BaseEvent, Event>::value, "Event 必須繼承 BaseEvent");
		auto& handlers = Registry<Event>::handlers;
		handlers.erase(std::remove_if(handlers.begin(), handlers.end(),
			[&listener](const HandlerPair& h) {
				return h.first.lock() == listener;
			}
		), handlers.end());
	}

	template<typename Event>
	void emit(Event& event) {
		static_assert(std::is_base_of<BaseEvent, Event>::value, "Event 必須繼承 BaseEvent");
		auto& handlers = Registry<Event>::handlers;

		for (auto it = handlers.begin(); it != handlers.end();) {
			if (auto sp = it->first.lock()) {
				it->second(event);
				++it;
			} else {
				it = handlers.erase(it);
			}
		}
	}
};

// 類外定義 static handlers
template<typename BaseListener, typename BaseEvent>
template<typename Event>	
std::vector<std::pair<std::weak_ptr<BaseListener>, std::function<bool(BaseEvent&)>>>
EventBus<BaseListener, BaseEvent>::Registry<Event>::handlers;