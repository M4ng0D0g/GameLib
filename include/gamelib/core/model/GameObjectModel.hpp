#pragma once

#include <memory>

namespace GameLib::Core {

	class GameObjectModel {
	public:
		using U_Ptr = std::unique_ptr<GameObjectModel>;
		using S_Ptr = std::shared_ptr<GameObjectModel>;
		using W_Ptr = std::weak_ptr<GameObjectModel>;

	protected:
		GameObjectModel();
		virtual ~GameObjectModel() = default;
		
		static uint64_t lastId_;
		const uint64_t id_;

	public:
		GameObjectModel(const GameObjectModel&);
		GameObjectModel& operator=(const GameObjectModel&) = default;

		uint64_t getId() { return id_; }
		// The id cannot be resetted.

		virtual void update() = 0;

	};

}
