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

private:
	template<typename Event>
	struct Registry {
		static_assert(std::is_base_of<BaseEvent, Event>::value, "Event 必須繼承 BaseEvent");

		using EventPtr = std::shared_ptr<Event>;
		using Handler = std::function<bool(EventPtr)>;
		using HandlerPair = std::pair<std::weak_ptr<BaseListener>, Handler>;

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
	void emit(EventPtr event) {
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

// ---

class E {
public:
	virtual ~E() = default;
	int data;
};

class E1 : public E {
public:
	E1() : E() {
		data = 10;
	}
};

class E2 : public E {
public:
	E2() : E() {
		data = 20;
	}
};

class L {
public:
	virtual ~L() = default;
};

class L1 : public L {
public:
	bool func1(std::shared_ptr<E> event) {
		std::cout << "L1.func1()" << std::endl;
		std::cout << event->data << std::endl;
		event->data = 10;
		return true;
	}
};

class L2 : public L {
public:
	bool func2(std::shared_ptr<E> event) {
		std::cout << "L1.func2()" << std::endl;
		std::cout << event->data << std::endl;
		event->data = 20;
		return true;
	}
};

int main() {
	auto MyEventBus = EventBus<L, E>();

	auto l1 = std::make_shared<L1>;
	auto l2 = std::make_shared<L2>;


	MyEventBus.subscribe<E1>(l1, [l1](std::shared_ptr<E> evt) {
		return l1->func1(std::static_pointer_cast<E1>(evt));
	});


}