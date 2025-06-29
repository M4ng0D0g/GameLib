#pragma once

#include <memory>

class BaseGameObject {
public:
	using Ptr = std::shared_ptr<BaseGameObject>;

protected:
	BaseGameObject();
	virtual ~BaseGameObject() = default;
	static size_t lastId_;

	const size_t id_;

public:
	BaseGameObject(const BaseGameObject&) = delete;
	BaseGameObject& operator=(const BaseGameObject&) = delete;

	size_t getId() { return id_; }
	// The id cannot be reseted.

	virtual void update() = 0;

};