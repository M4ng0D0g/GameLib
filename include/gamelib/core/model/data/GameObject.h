#pragma once

#include <memory>

class GameObject {
public:
	using SPtr = std::shared_ptr<GameObject>;

protected:
	GameObject();
	virtual ~GameObject() = default;
	static size_t lastId_;

	const size_t id_;

public:
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	size_t getId() { return id_; }
	// The id cannot be reseted.

	virtual void update() = 0;

};