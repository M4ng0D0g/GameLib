#pragma once

#include "Entity.hpp"
#include "ComponentBase.hpp"
#include <memory>
#include <unordered_map>

// TODO: 要求 C 繼承自 ComponentBase

namespace gamelib::game::model::ecs {

	class ComponentStorage {
	public:
		
		template <typename C>
		void add(Entity e, std::shared_ptr<C> comp) {
			auto& map = getMap<C>();
			map[e] = comp;
		}

		template <typename C>
		void remove(Entity e) {
			getMap<C>().erase(e);
		}

		template <typename C>
		std::shared_ptr<C> get(Entity e) {
			auto& map = getMap<C>();
			auto it = map.find(e);
			return it != map.end() ? std::static_pointer_cast<C>(it->second) : nullptr;
		}

	
	private:
		template <typename C>
		std::unordered_map<Entity, std::shared_ptr<C>>& getMap() {
			static std::unordered_map<Entity, std::shared_ptr<C>> inst;
			return inst;
		}
	};
	
}