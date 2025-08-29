#pragma once
#include "Uuid.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <random>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <cstdlib>
#endif

/********************************************************************************/

namespace gamelib::utils {

	class Terminal {
	public:
		Terminal(const std::string& title = "Console Window") {
			#ifdef _WIN32
				AllocConsole();
				freopen_s(&fpOut_, "CONOUT$", "w", fpOut_);
				std::fprintf(fpOut_, "=== %s Opened (Windows) ===\n", title.c_str());
			#else
				tempFile_ = "/tmp/game_console_output_" + uuidv4() + ".txt";
				out_.open(tempFile_);

				std::string cmd = "xterm -T \"" + title + "\" -hold -e tail -f " + tempFile_ + " &";
				system(cmd.c_str());
				out_ << "=== " << title << " Opened (Unix) ===" << std::endl;
				out_.flush();
			#endif
		}
		~Terminal() {
			#ifdef _WIN32
				if (fpOut_) fclose(fpOut_);
			#else
				if (out_.is_open()) out_.close();
				if (!tempFile_.empty()) std::remove(tempFile_.c_str());
			#endif
		}

		void write(const std::string& msg) {
			#ifdef _WIN32
				if (fpOut_) std::fprintf(fpOut, "%s\n", msg.c_str());
			#else
				if (out_.is_open()) {
					out_ << msg << std::endl;
					out_.flush();
				}
			#endif
		}

	private:
		#ifdef _WIN32
			FILE* fpOut_ = nullptr;
		#else
			std::ofstream out_;
			std::string tempFile_;
		#endif
	};


}

/********************************************************************************/

#include <clocale>
#include <codecvt>
#include <locale>
#include <string>

// 估計一段 UTF-8 字串在等寬終端機中要佔幾個字元寬度
int displayWidth(const std::string& utf8) {
	// 建議在 main() 先 setlocale(LC_CTYPE, "");
	thread_local static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
	std::u32string u32;
	try {
		u32 = conv.from_bytes(utf8);
	} catch (...) {
		return 0; // 或者改用替代字元策略
	}

	int w = 0;

	#if WCHAR_MAX >= 0x10FFFF
		for (char32_t ch : u32) {
			int cw = ::wcwidth(static_cast<wchar_t>(ch));
			if (cw > 0) w += cw;
		}
	#else
		// Windows / wchar_t 16-bit：改呼叫你整合的 mk_wcwidth(ch) 或其他寬度表
		for (char32_t ch : u32) {
			int cw = mk_wcwidth(ch); // 需自備實作
			if (cw > 0) w += cw;
		}
	#endif
		return w; // 不強制 >= 1 較直觀
}

