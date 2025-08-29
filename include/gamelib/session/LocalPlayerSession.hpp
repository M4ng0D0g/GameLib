#pragma once

#include "gamelib/game/view/IView.hpp"
#include "gamelib/graphics/IWindow.hpp"

namespace gamelib::session {

	class LocalPlayerSession : public game::view::IView {
	public:

		void update(const game::view::RenderMessage& msg) override;
	

	private:
		graphics::IWindow window_;
	};
}