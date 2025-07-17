#pragma once

#include "Event.hpp"
#include "Listener.hpp"
#include <iostream>
#include <functional>
#include <utility>
#include <vector>
#include <memory>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <mutex>

namespace GameLib::Core {

	class Event;
	
	class EventBus {
	public:
		using Token = size_t;

	private:
		std::mutex mutex_;
		Token nextToken_ = 1;

		template<typename T>
		struct Registry {
			static_assert(std::is_base_of<Event, T>::value, "T 必須繼承自 Event");

			static std::vector<Listener<T>::W_Ptr> handlers;
		};

	public:
		virtual ~EventBus() = default;

		template <typename T>
		void subscribe(Listener<Event>::W_Ptr listener);

		template <typename Event>
		void unsubscribe(Listener<Event>::W_Ptr listener);
		
		template <typename Event>
		void emit(Event& event);
	};




		
	// 類外定義 static handlers
	template<typename BaseListener, typename BaseEvent>
	template<typename Event>	
	std::vector<std::pair<std::weak_ptr<BaseListener>, std::function<bool(BaseEvent&)>>>
	EventBus<BaseListener, BaseEvent>::Registry<Event>::handlers;
}

