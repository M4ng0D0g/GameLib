#pragma once

#include <enet/enet.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <variant>
#include <nlohmann/json.hpp>

// ***************************************************************************/



class Packet {
public:
	using Payload = std::variant<
		std::monostate,
		int,
		std::string,
		std::vector<int>,
		std::vector<std::string>,
		std::unordered_map<std::string, int>
	>;

private:
	int version_ = 1;
	std::string corrId_;
	std::string event_;
	std::unordered_map<std::string, Payload> payload_;
	
public:
	Packet(
		const std::string& event,
		const std::unordered_map<std::string, Payload>& payload,
		const std::string& corrId = ""
	) : event_(event), payload_(payload), corrId_(corrId) {}

	int getVersion() const { return version_; }
	std::string getCorreId() const { return corrId_; }
	std::string getEvent() const { return event_; }

	const std::unordered_map<std::string, Payload>& getPayload() const {
		return payload_;
	}

	void setPayload(const std::string& key, const Payload& value) {
		if(!payload_.contains(key)) throw std::invalid_argument("Invalid payload key: " + key);
		payload_[key] = value;
	}
	
};
	