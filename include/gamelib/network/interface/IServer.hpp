#pragma once

namespace gamelib::network::interface {
	
	class IServer {
	public:
		virtual ~IServer() = default;

		virtual void start() = 0;
		virtual void stop() = 0;
	};

}