#pragma once

#include "Packet.h"
#include <enet/enet.h>
#include <nlohmann/json.hpp>

// ***************************************************************************/

class PacketHandler {
public:
	static json parseObject(ENetEvent& event);
	static json parseObject(const Packet& env);
};