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

namespace GameLib::Core::Event {

	class Event;
	using Token = size_t;
	
	class EventBus {
	public:
		template <typename T>
		using ListenerW_Ptr = typename Listener<T>::W_Ptr;

		template<typename T>
		struct Registry {
			static_assert(std::is_base_of<Event, T>::value, "T 必須繼承 Event");
			static std::vector<ListenerW_Ptr<T>> handlers;
		};

	private:
		std::mutex mutex_;
		Token nextEventToken_ = 1;

	public:
		virtual ~EventBus() = default;

		template <typename T>
		void subscribe(ListenerW_Ptr<T> listener) {
			static_assert(std::is_base_of<Event, T>::value, "T 必須繼承 Event");
			std::scoped_lock lock(mutex_);

			Registry<T>::handlers.push_back(listener);
		}

		template <typename T>
		void unsubscribe(ListenerW_Ptr<T> listener) {
			static_assert(std::is_base_of<Event, T>::value, "T 必須繼承 Event");
			std::scoped_lock lock(mutex_);

			auto& list = Registry<T>::handlers;
			list.erase(std::remove_if(list.begin(), list.end(),
				[&listener](const auto& h) {
					return h.lock() == listener.lock();
				}	
			), list.end());
		}
		
		template <typename T>
		void publish(std::shared_ptr<T>& event) {
			static_assert(std::is_base_of<Event, T>::value, "T 必須繼承 Event");
			std::scoped_lock lock(mutex_);

			auto& list = Registry<T>::handlers;
			for (auto it = list.begin(); it != list.end();) {
				if (auto sp = it->lock()) {
					sp->onEvent(event);
					++it;
				} else {
					it = list.erase(it);
				}
			}
		}
	};

	// 靜態成員定義，必須明確寫出
	template<typename T>
	std::vector<typename Listener<T>::W_Ptr> EventBus::Registry<T>::handlers;




		
	// 類外定義 static handlers
	// template<typename BaseListener, typename BaseEvent>
	// template<typename Event>	
	// std::vector<std::pair<std::weak_ptr<BaseListener>, std::function<bool(BaseEvent&)>>>
	// EventBus<BaseListener, BaseEvent>::Registry<Event>::handlers;
}

