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

using Token = size_t;

namespace gamelib::event {

	class Event;

	class EventBus {
	public:
		virtual ~EventBus() = default;

		// --------------------------------------------------------------------------------

		template <typename T>
		void subscribe(std::weak_ptr<Listener<T>> listener) {
			static_assert(std::is_base_of<Event, T>::value, "T 必須繼承 Event");

			std::scoped_lock lock(mutex_);
			if (!listener.expired()) Registry<T>::listeners().emplace_back(listener);
		}

		template <typename T>
		void unsubscribe(std::weak_ptr<Listener<T>> listener) {
			static_assert(std::is_base_of<Event, T>::value, "T 必須繼承 Event");

			std::scoped_lock lock(mutex_);
			auto& list = Registry<T>::listeners();
			list.erase(std::remove_if(list.begin(), list.end(),
				[&listener](const auto& h) {
					return h.lock() == listener.lock();
				}),
				list.end()
			);
		}
		
		// --------------------------------------------------------------------------------

		template <typename T>
		void publish(std::shared_ptr<T> event) {
			static_assert(std::is_base_of<Event, T>::value, "T 必須繼承 Event");

			std::scoped_lock lock(mutex_);
			Registry<T>::cleanup();

			auto& list = Registry<T>::listeners();
			for (const auto& wptr : list) {
				if (auto sp = wptr.lock()) sp->onEvent(event);
			}
		}

	private:
		template<typename T>
		struct Registry {
			static_assert(std::is_base_of<Event, T>::value, "T 必須繼承 Event");

			static void cleanup() {
				auto& list = listeners();
				list.erase(
					std::remove_if(list.begin(), list.end(),
					[](const std::weak_ptr<Listener<T>>& wptr) {
						return wptr.expired();
					}),
					list.end()
				);
			}

			static std::vector<std::weak_ptr<Listener<T>>>& listeners() {
				static std::vector<std::weak_ptr<Listener<T>>> instance;
				return instance;
			}
		};

		std::mutex mutex_;
		Token nextEventToken_ = 1;

	};

	// 靜態成員定義，必須明確寫出
	// template<typename EventT>
	// std::vector<std::weak_ptr<Listener<EventT>>> EventBus::Registry<EventT>::handlers;

	template<typename BaseE, typename BaseL>
	class EventBusT {
		static_assert(std::is_base_of<Event, BaseE>::value, "BaseE 必須繼承 Event");
		static_assert(std::is_base_of<Listener<BaseE>, BaseL>::value, "BaseL 必須繼承 Listener<BaseE>");

	public:
		virtual ~EventBusT() = default;

		// --------------------------------------------------------------------------------

		template <typename DerivedE>
		void subscribe(std::weak_ptr<BaseL<DerivedE>> listener) {
			static_assert(std::is_base_of<BaseE, DerivedE>::value, "DerivedE 必須繼承 BaseE");

			std::scoped_lock lock(mutex_);
			if (!listener.expired()) Registry<DerivedE>::listeners().emplace_back(listener);
		}

		template <typename DerivedE>
		void unsubscribe(std::weak_ptr<BaseL<DerivedE>> listener) {
			static_assert(std::is_base_of<BaseE, DerivedE>::value, "DerivedE 必須繼承 BaseE");

			std::scoped_lock lock(mutex_);
			auto& list = Registry<T>::listeners();
			list.erase(std::remove_if(list.begin(), list.end(),
				[&listener](const auto& h) {
					return h.lock() == listener.lock();
				}),
				list.end()
			);
		}
		
		// --------------------------------------------------------------------------------

		template <typename DerivedE>
		void publish(std::shared_ptr<DerivedE> event) {
			static_assert(std::is_base_of<BaseE, DerivedE>::value, "DerivedE 必須繼承 BaseE");

			std::scoped_lock lock(mutex_);
			Registry<DerivedE>::cleanup();

			auto& list = Registry<DerivedE>::listeners();
			for (const auto& wptr : list) {
				if (auto sp = wptr.lock()) sp->onEvent(event);
			}
		}

	private:
		template<typename DerivedE>
		struct Registry {
			static_assert(std::is_base_of<BaseE, DerivedE>::value, "DerivedE 必須繼承 BaseE");

			static void cleanup() {
				auto& list = listeners();
				list.erase(
					std::remove_if(list.begin(), list.end(),
					[](const std::weak_ptr<BaseL<DerivedE>>& wptr) {
						return wptr.expired();
					}),
					list.end()
				);
			}

			static std::vector<std::weak_ptr<BaseL<DerivedE>>>& listeners() {
				static std::vector<std::weak_ptr<BaseL<DerivedE>>> instance;
				return instance;
			}
		};

		std::mutex mutex_;
		Token nextEventToken_ = 1;

	};
		
	// 類外定義 static handlers
	// template<typename BaseListener, typename BaseEvent>
	// template<typename Event>	
	// std::vector<std::pair<std::weak_ptr<BaseListener>, std::function<bool(BaseEvent&)>>>
	// EventBus<BaseListener, BaseEvent>::Registry<Event>::handlers;
}

