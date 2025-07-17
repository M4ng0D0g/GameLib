#pragma once

#include "EventBus.hpp"
#include "Event.hpp"
#include <memory>

namespace GameLib::Core {

	class EventBus;
	class Event;

	template <typename T>
	class Listener {
		static_assert(std::is_base_of<Event, T>::value, "T 必須繼承自 Event");

	public:
		using U_Ptr = std::unique_ptr<Listener>
		using S_Ptr = std::shared_ptr<Listener>;
		using W_Ptr = std::weak_ptr<Listener>;

		virtual ~Listener() = default;

		virtual bool onEvent(const T::S_Ptr&) = 0;
		virtual void subscribeAll(EventBus&) {}
	};
}
