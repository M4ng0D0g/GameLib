/*
	
class PieceViewModel {
public:
    const PieceModel& model;

    PieceViewModel(const PieceModel& m) : model(m) {}

    char getAscii() const {
        if (model.hp <= 0) return 'X';
        return '@';
    }

    Color getColor() const {
        return (model.hp > 50) ? Color::Green : Color::Red;
    }
};

*/

/*
	struct PieceModel {
		int type;
		int hp;
		int x, y;
	};

	struct RenderInfo {
		char ascii;
		std::vector<Color> colors;
	};

	std::unordered_map<int, RenderInfo> pieceRenderMap;

	*/