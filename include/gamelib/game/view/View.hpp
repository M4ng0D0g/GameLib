#pragma once

#include <memory>

namespace GameLib::Core {

	class View {
	public:
		using U_Ptr = std::unique_ptr<View>;

		virtual void update() = 0;
		virtual void render() const = 0;
	};
	// class View {
	// public:
	// 	virtual void show() = 0;
	// 	virtual void hide() = 0;
	// 	virtual void update(const std::string& msg) = 0;
	// 	virtual ~View() = default;
	// };
}

