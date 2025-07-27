#pragma once

namespace GameLib::Network::Interface {
	
	class IServer {
	public:
		virtual ~IServer() = default;

		virtual void start() = 0;
		virtual void stop() = 0;
	};

}