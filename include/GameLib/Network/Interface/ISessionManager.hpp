#pragma once

#include "GameLib/Network/Base/Session.hpp"
#include "GameLib/Utils/Uuid.hpp"
#include "GameLib/Utils/Time.hpp"

namespace GameLib::Network::Interface {
	
	class ISessionManager {
	public:
		virtual ~ISessionManager() = default;
		
		virtual void registerSession() = 0;
		virtual void unregisterSession(const Utils::uuid& id) = 0;
		virtual Base::Session::S_Ptr findById(const Utils::uuid& id) = 0;

		virtual void tick(Utils::StedayClock::time_point now) = 0;
	};

}