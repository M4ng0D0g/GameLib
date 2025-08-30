#pragma once
#include "gamelib/utils/AnsiPrint.hpp"
#include "UIIcon.hpp"
#include "gamelib/utils/Unit.hpp"
#include <vector>
#include <memory>
#include <string>

namespace gamelib::graphics::console::ui {

	using Layer = std::vector<std::vector<UICell>>;
	using LayerBuffer = std::vector<Layer>;

	// 初始化 0~maxPriority(含) 的 layer(w*h)
	LayerBuffer initLayerBuffer(int width, int height, int maxPriority) {
		LayerBuffer layers;
		for(int i = 0; i <= maxPriority; ++i) {
			layers.push_back(Layer(height, std::vector<Cell>(width)));
		}
		return layers;
	}

	void renderToLayer(UIElement* elem, LayerBuffer& layers) {
		if(!elem) return;

		int layerIndex = elem->priority;
		Layer& layer = layers[layerIndex];

		for(int dy = 0; dy < elem->size.height; ++dy) {
			int row = elem->position.y + dy;
			if(row < 0 || row >= layer.size()) continue;

			for(int dx = 0; dx < elem->size.width; ++dx) {
				int col = elem->position.x + dx;
				if(col < 0 || col >= layer[0].size()) continue;

				std::string c = (dx < elem->content[dy].size()) ? std::string(1, elem->content[dy][dx]) : " ";
				layer[row][col] = {c, elem->fg, elem->bg};
			}
		}

		// 遞迴渲染子元素
		for(auto* child : elem->children) {
			renderToLayer(child, layers);
		}
	}

	Layer mergeLayers(const LayerBuffer& layers) {
		int height = layers[0].size();
		int width  = layers[0][0].size();
		std::vector<std::vector<Cell>> screen(height, std::vector<Cell>(width));

		for(int r = 0; r < height; ++r) {
			for(int c = 0; c < width; ++c) {
				// 從低到高 priority
				for(int p = 0; p < layers.size(); ++p) {
					const Cell& cell = layers[p][r][c];
					if(!cell.empty()) {
						screen[r][c] = cell;
					}
				}
			}
		}
		return screen;
	}


	
}


