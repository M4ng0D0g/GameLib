#pragma once

#include <memory>

namespace GameLib::Core {

	class IView {
	public:
		using U_Ptr = std::unique_ptr<IView>;

		virtual void update() = 0;
		virtual void render() const = 0;
	};
}

