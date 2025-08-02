#pragma once

#include "EventBus.hpp"
#include "Event.hpp"
#include <memory>
#include <type_traits>

namespace gamelib::event {

	class EventBus;
	class Event;

	template <typename T>
	class Listener : public std::enable_shared_from_this<Listener<T>> {
		static_assert(std::is_base_of<Event, T>::value, "T 必須繼承自 Event");

	public:
		virtual ~Listener() = default;

		virtual bool onEvent(std::shared_ptr<T> event) = 0;
		virtual void autoRegister(EventBus&) {}
	};
}
