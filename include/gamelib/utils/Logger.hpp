#pragma once

#include <string>
#include <mutex>
#include <fstream>
#include <memory>

namespace GameLib::Utils::Logger {

	enum class Level {
		Info,
		Warning,
		Error,
		Debug
	};

	class Logger {
	public:
		static Logger& instance();

		void setLogFile(const std::string& filename);
		void setEnableColor(bool enabled);
		void log(Level level, const std::string& message);

		void info(const std::string& message);
		void warn(const std::string& message);
		void error(const std::string& message);
		void debug(const std::string& message);

	private:
		Logger();
		std::string getTimestamp();
		std::string levelToString(Level level);
		std::string levelToColor(Level level);

		std::ofstream logFile_;
		bool colorEnabled_ = true;
		std::mutex mutex_;
	};
}
