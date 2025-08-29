#pragma once

#include "Entity.hpp"
#include "ComponentStorage.hpp"
#include <vector>

namespace gamelib::game::model::ecs {

	class SystemBase {
	public:
		virtual ~SystemBase() = default;

		// 處理所有實體的邏輯，dt 為 delta-time
		virtual void Update(double dt, ComponentStorage& store, const std::vector<Entity>& entities) = 0;
	};
	
}