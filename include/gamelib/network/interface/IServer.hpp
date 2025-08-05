#pragma once

namespace gamelib::network::interface {
	
	class IServer {
	public:
		virtual ~IServer() = default;

		virtual bool start() = 0;
		virtual bool stop() = 0;
	};

}