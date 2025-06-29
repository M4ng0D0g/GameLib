#include "model/object/BaseGameObject.h"


size_t BaseGameObject::lastId_ = 0;

BaseGameObject::BaseGameObject() : id_(++lastId_) {}
