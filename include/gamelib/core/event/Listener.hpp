#pragma once

#include "EventBus.hpp"
#include "Event.hpp"
#include <memory>
#include <type_traits>

namespace GameLib::Core::Event {

	class EventBus;
	class Event;

	template <typename T>
	class Listener : public std::enable_shared_from_this<Listener<T>> {
		static_assert(std::is_base_of<Event, T>::value, "T 必須繼承自 Event");

	public:
		using U_Ptr = std::unique_ptr<Listener>;
		using S_Ptr = std::shared_ptr<Listener>;
		using W_Ptr = std::weak_ptr<Listener>;

		virtual ~Listener() = default;

		virtual bool onEvent(const std::shared_ptr<T>&) = 0;
		virtual void autoRegister(EventBus&) {}
	};
}
