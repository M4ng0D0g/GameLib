#include "view/View.h"
#include "GameConfig.h"
#include "view/AnsiPrint.h"
#include <codecvt>      // std::wstring_convert
#include <cwchar>       // wcwidth
#include <sys/ioctl.h>   // winsize, TIOCGWINSZ
#include <unistd.h>  //  STDOUT_FILENO
#include <iostream>
#include <locale>
#include <utility>

// return the actual length in terminal of a string.
int displayWidth(const std::string& utf8) {
    static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    auto u32 = conv.from_bytes(utf8);

    int w = 0;
    for (char32_t ch : u32)
    w += std::max(0, ::wcwidth(static_cast<wchar_t>(ch)));
    return std::max(1, w);
}

View::View(const GameConfig& config, Model& model) : config_(config), model_(model) {
    std::setlocale(LC_ALL, "");
    
    auto make_str_buf = [config] {
        return std::vector<std::vector<std::string>>(
            config.GAME_WINDOW.height, std::vector<std::string>(config.GAME_WINDOW.width, ""));
    };
    auto make_col_buf = [config] {
        return std::vector<std::vector<AnsiColor::Ptr>>(
            config.GAME_WINDOW.height, std::vector<AnsiColor::Ptr>(
                config.GAME_WINDOW.width,
                AnsiColor::Basic(9)
            )
        );
    };

    latest_map   = last_map   = make_str_buf();
    latest_fg_color = last_fg_color = make_col_buf();
    latest_bg_color = last_bg_color = make_col_buf();
    resetLatest();

}

void View::updateGameObject() {
    const auto& board = model_.getBoard();

    for(const auto& list : board) {
        for(const Viewable::Ptr& obj : list) {
            if(!obj) continue;

            const Icon& icon = obj->getIcon();
            const Pos2& pos  = obj->getPosition();
            // std::cout << "test" << std::endl;


            const int baseRow = pos.y * config_.GAME_WINDOW_SCALE.height;
            const int baseCol = pos.x * config_.GAME_WINDOW_SCALE.width;

            const int iconHeight = static_cast<int>(icon.size());

            for(int dy = 0; dy < iconHeight; ++dy) {
                int row = baseRow + dy;
                if(row < 0 || row >= config_.GAME_WINDOW.height) continue;

                const int iconWidth = static_cast<int>(icon[dy].size());

                for(int dx = 0; dx < iconWidth; ++dx) {
                    int col = baseCol + dx;
                    if(col < 0 || col >= config_.GAME_WINDOW.width) continue;

                    const Cell& cell = icon[dy][dx];
                    latest_map [row][col] = cell.ascii;
                    latest_bg_color[row][col] = cell.color;
                }
            }
        }
    }
}

void View::render(){
    auto [rows, cols] = get_terminal_size();
    bool resized = (rows != _termHeight || cols != _termWidth);
    _termHeight = rows;
    _termWidth  = cols;

    if (resized) std::cout << "\033[2J\033[H";

    bool dirty = (   last_map      != latest_map
        || last_fg_color != latest_fg_color
        || last_bg_color != latest_bg_color);
    if (!dirty) return;

    std::string frame;
    frame.reserve(
        (config_.GAME_WINDOW.height + 2) * (config_.GAME_WINDOW_CELL.width * config_.GAME_WINDOW.width + 3)
    );


    // Top line

    frame += '+' + std::string(config_.GAME_WINDOW.width * config_.GAME_WINDOW_CELL.width, '-') + "+\n";

    for (int r = 0; r < config_.GAME_WINDOW.height; ++r) {
        int rowScreen = r + 2;

        // Left line
        frame += '|';

        int pixelCol = 1;

        for (int c = 0; c < config_.GAME_WINDOW.width; ++c) {
            const std::string& txt = latest_map[r][c];
            const auto         fg  = latest_fg_color[r][c];
            const auto         bg  = latest_bg_color[r][c];

            int w        = std::max(1, displayWidth(txt));
            int padTotal = config_.GAME_WINDOW_CELL.width - w;
            int padLeft  = padTotal / 2;
            int padRight = padTotal - padLeft;

            // Left blank
            for (int p = 0; p < padLeft; ++p) {
                auto fg = AnsiColor::Basic(9);
                frame += AnsiPrint(" ", fg, bg, false, false);
            }

            // icon 
            frame += AnsiPrint(txt.c_str(), fg, bg, false, false);

            // Right 
            for (int p = 0; p < padRight; ++p) {
                auto fg = AnsiColor::Basic(9);
                frame += AnsiPrint(" ", fg, bg, false, false);
            }

            pixelCol += config_.GAME_WINDOW_CELL.width;
        }


        // Right line
        frame += "|\n";

    }
    // Bottom line
    frame += '+' + std::string(config_.GAME_WINDOW.width * config_.GAME_WINDOW_CELL.width, '-') + "+\n";

    std::cout << "\033[H" << frame << std::flush;


    // update buffer
    last_map      = latest_map;
    last_fg_color = latest_fg_color;
    last_bg_color = latest_bg_color;
}

void View::displayScore() {

}

void View::resetLatest(){
    for (int r = 0; r < config_.GAME_WINDOW.height; ++r) {
        std::fill(latest_map[r].begin(),   latest_map[r].end(),   " ");
        std::fill(latest_fg_color[r].begin(), latest_fg_color[r].end(), AnsiColor::Basic(9));
        std::fill(latest_bg_color[r].begin(), latest_bg_color[r].end(), AnsiColor::Basic(9));
    }
}
std::pair<int,int> View::get_terminal_size() {
    int rows, cols;
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        rows = w.ws_row;
        cols = w.ws_col;
    } else {
        rows = cols = -1; // Error case
    }
    return std::make_pair(rows, cols);
}

