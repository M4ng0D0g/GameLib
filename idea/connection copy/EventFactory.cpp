#include "connection/event/EventFactory.h"

IEvent::Ptr EventFactory::create(const ClientSession::Ptr& sender, const json& obj) {
	const std::string& eventName = obj["event"];
	const json& payload = obj["payload"];

	if (eventName == "HandshakeEvent") {
		auto event = HandshakeEvent::create();
		event->sender_ = sender;
		event->token_ = payload["token"];
		return event;
	}
	

	return nullptr;
}