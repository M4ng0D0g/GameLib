#include "gamelib/core/event/EventBus.hpp"

template <typename Event>
void subscribe(ListenerPtr listener, Handler handler) {
	static_assert(std::is_base_of<BaseEvent, Event>::value, "Event 必須繼承 BaseEvent");
	Registry<Event>::handlers.emplace_back(listener, std::move(handler));
}

template <typename Event>
void unsubscribe(ListenerPtr listener) {
	static_assert(std::is_base_of<BaseEvent, Event>::value, "Event 必須繼承 BaseEvent");
	auto& handlers = Registry<Event>::handlers;
	handlers.erase(std::remove_if(handlers.begin(), handlers.end(),
		[&listener](const HandlerPair& h) {
			return h.first.lock() == listener;
		}
	), handlers.end());
}
template <typename Event>
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