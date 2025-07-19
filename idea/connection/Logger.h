#pragma once;

#include <string>
#include <iostream>
#include <enet/enet.h>

// ***************************************************************************/

class Logger {
public:
	static void server_create(enet_uint32 host, enet_uint16 port) {
		std::cout << "Succeeded to create Server on " << host << ":" << port << std::endl;
	}
	static void server_connect(ENetEvent& event) {
		std::cout << "Client " << event.peer->address.host
		<< ":" << event.peer->address.port << " connected.\n";
	}
	static void server_disconnect(ENetEvent& event) {
		std::cout << "Client " << event.peer->address.host
		<< ":" << event.peer->address.port << " disconnected.\n";
	}
	static void server_stop() {
		std::cout << "Server stopped completely" << std::endl;
	}
	static void server_receivePacket(ENetEvent& event) {
		std::cout << "[Packet]"
		<< "\nChannel: " << event.channelID
		<< "\nClient: " << event.peer->address.host << ":" <<  event.peer->address.port << "\n";
	}

	static void info(const std::string& info) {
		std::cout << info << std::endl;
	}
	static void warn(const std::string& info, const std::string& data) {
		std::cout << info << data << std::endl;
	}
};