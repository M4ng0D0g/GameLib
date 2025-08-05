#pragma once

#include <gamelib/Event.hpp>

namespace gamelib::common {

	class EngineE : public event::Event {};
	class EngineL : public event::Listener<EngineE> {};
	class EngineEB : public event::EventBusT<EngineE, EngineL> {};
	
}