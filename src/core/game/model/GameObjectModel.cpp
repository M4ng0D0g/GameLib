#include "gamelib/core/model/GameObjectModel.hpp"

namespace GameLib::Core {

	size_t GameObjectModel::lastId_ = 0;

	GameObjectModel::GameObjectModel() : id_(++lastId_) {}
	GameObjectModel::GameObjectModel(const GameObjectModel& other) : id_(++lastId_) {}

}
