#pragma once

#include "Packet.h"

// ***************************************************************************/	

class PacketBuilder {
public:
	enum class Type { 
		Welcome,
	};

private:
	Packet packet_;

public:
	PacketBuilder(PacketBuilder::Type type, const std::string& corrId = "")
	: packet_(eventName(type), defaultPayload(type), corrId) {}

	PacketBuilder& with(const std::string& key, const Packet::Payload& value, bool allowNull = false) {
		packet_.setPayload(key, value);
		return *this;
	}

	Packet build() {
		return packet_;
	}

private:
	std::string eventName(PacketBuilder::Type t);
	json defaultPayload(PacketBuilder::Type t);
	
};