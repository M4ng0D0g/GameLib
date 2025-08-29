#include "connection/PacketHandler.h"
#include "utils/uuid.h"
#include "utils/time.h"
#include <iostream>
#include <string>

json PacketHandler::parseObject(ENetEvent& event) {
	std::string raw(reinterpret_cast<char*>(event.packet->data), event.packet->dataLength);
	try {
		return json::parse(raw);
	}
	catch(const json::parse_error& e) {
		std::cerr << "[JSON parse error] " << e.what() << "\n";
		return {};
	}
}

json PacketHandler::parseObject(const Packet& env) {
	json obj = {
		{"header", {
			{"version", env.getVersion()},
			{"messageId", uuid::generateV4()},
			{"timestamp", Time::steadyNowMs()},
			{"correlationId", env.getCorreId()}
		}},
		{"event", env.getEvent()},
		{"payload", json::object()}
	};
	for(auto& [key, value] : env.getPayload()) {
		std::visit([&](auto&& v){
			using T = std::decay_t<decltype(v)>;
			if constexpr(std::is_same_v<T, std::monostate>) obj["payload"][key] = nullptr;
			else if constexpr(std::is_same_v<T, int>) obj["payload"][key] = v;
			else if constexpr(std::is_same_v<T, std::string>) obj["payload"][key] = v;
			else if constexpr(std::is_same_v<T, std::vector<int>>) obj["payload"][key] = v;
			else if constexpr(std::is_same_v<T, std::vector<std::string>>) obj["payload"][key] = v;
			else if constexpr(std::is_same_v<T, std::unordered_map<std::string, int>>) obj["payload"][key] = v;
		}, value);
	}
	return obj;
}