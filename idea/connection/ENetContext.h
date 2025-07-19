#pragma once

#include <iostream>
#include <stdexcept>
#include <enet/enet.h>

// ***************************************************************************/

class ENetContext {
public:
	ENetContext() {
		if(enet_initialize() != 0) throw std::runtime_error{"ENet initialize failed!"};
	}
	~ENetContext() {
		enet_deinitialize();
	}
	ENetContext(const ENetContext&) = delete;
	ENetContext& operator=(const ENetContext&) = delete;
};