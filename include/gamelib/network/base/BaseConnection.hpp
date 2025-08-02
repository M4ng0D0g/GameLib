#pragma once

#include "gamelib/utils/Uuid.hpp"
#include <boost/asio.hpp>
#include <thread>
#include <atomic>

namespace gamelib::network::base {

	class BaseConnection {
	public:
		BaseConnection(const utils::uuid& id) : serverId_(id) {}
		virtual ~BaseConnection() = default;

	protected:
		boost::asio::io_context ioContext_;
		std::thread ioThread_;
		utils::uuid serverId_;
		std::atomic<bool> running_{false};
	};

}