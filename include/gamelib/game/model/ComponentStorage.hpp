#pragma once

#include "Entity.hpp"
#include "Component.hpp"
#include <memory>
#include <unordered_map>

namespace gamelib::game {

	class ComponentStorage {
	public:
		
		template <typename C>
		void add(Entity entity, std::shared_ptr<C> comp) {
			auto& map = getMap<C>();
			map[e] = comp;
		}

		template <typename C>
		void remove(Entity entity) {
			getMap<C>().erase(entity);
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