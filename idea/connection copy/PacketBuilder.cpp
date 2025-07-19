#include "connection/PacketBuilder.h"

std::string PacketBuilder::eventName(PacketBuilder::Type t) {
	switch(t) {
		case PacketBuilder::Type::Welcome: return "Welcome";
	}
	return "";
}

json PacketBuilder::defaultPayload(PacketBuilder::Type t) {
	switch (t) {
		case PacketBuilder::Type::Welcome:
			return json{{"serverId", ""}};
	}
	return json::object();
}