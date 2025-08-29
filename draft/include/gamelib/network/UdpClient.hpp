#pragma once

#include "GameLib/Network/Base/Client.hpp"
#include <boost/asio.hpp>
#include <iostream>

namespace GameLib::Network {

	class UdpClient : public Base::Client {
	private:
		boost::asio::ip::udp::socket socket_;
		boost::asio::ip::udp::endpoint remoteEndpoint_;
		
	public:
		UdpClient(const std::string& host, unsigned short port) : socket_(ioContext_) {
			remoteEndpoint_ = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(host), port);
			socket_.open(boost::asio::ip::udp::v4());
		}

		void send(const std::string& message) override {
			socket_.send_to(boost::asio::buffer(message), remoteEndpoint_);
		}

	
	};

}