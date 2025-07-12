#include "model/GameObject.h"


size_t GameObject::lastId_ = 0;

GameObject::GameObject() : id_(++lastId_) {}
