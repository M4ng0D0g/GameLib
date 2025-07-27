#pragma once

#include "GameLib/Network/Base/Session.hpp"
#include "GameLib/Utils/Uuid.hpp"
#include "GameLib/Utils/Time.hpp"

namespace GameLib::Network::Interface {
	
	class ISessionManager {
	public:
		virtual ~ISessionManager() noexcept = default;
		
		// virtual void createSession(std::shared_ptr<Base::Session> session) = 0;
		// virtual void registerSession(const Utils::uuid& id, std::shared_ptr<Base::Session> session) = 0;
		virtual void unregisterSession(const Utils::uuid& id) = 0;
		virtual std::shared_ptr<Base::Session> find(const Utils::uuid& id) = 0;

		virtual void tick(std::chrono::steady_clock::time_point now) = 0;
	};

}