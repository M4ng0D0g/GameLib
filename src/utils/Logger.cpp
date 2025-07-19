#include "gamelib/utils/Logger.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace GameLib::Utils::Logger {

	Logger& Logger::instance() {
		static Logger logger;
		return logger;
	}

	Logger::Logger() {}

	void Logger::setLogFile(const std::string& filename) {
		std::lock_guard<std::mutex> lock(mutex_);
		logFile_.open(filename, std::ios::out | std::ios::app);
	}

	void Logger::setEnableColor(bool enabled) {
		colorEnabled_ = enabled;
	}

	void Logger::log(Level level, const std::string& message) {
		std::lock_guard<std::mutex> lock(mutex_);

		std::string timestamp = getTimestamp();
		std::string levelStr = levelToString(level);
		std::string color = colorEnabled_ ? levelToColor(level) : "";

		std::string formatted = "[" + timestamp + "] [" + levelStr + "] " + message;

		// Console output
		if (colorEnabled_) {
			std::cout << color << formatted << "\033[0m" << std::endl;
		} else {
			std::cout << formatted << std::endl;
		}

		// File output
		if (logFile_.is_open()) {
			logFile_ << formatted << std::endl;
		}
	}

	void Logger::info(const std::string& message) {
		log(Level::Info, message);
	}

	void Logger::warn(const std::string& message) {
		log(Level::Warning, message);
	}

	void Logger::error(const std::string& message) {
		log(Level::Error, message);
	}

	void Logger::debug(const std::string& message) {
		log(Level::Debug, message);
	}

	std::string Logger::getTimestamp() {
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		std::tm tm{};
	#ifdef _WIN32
		localtime_s(&tm, &time);
	#else
		localtime_r(&time, &tm);
	#endif
		std::ostringstream oss;
		oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	std::string Logger::levelToString(Level level) {
		switch (level) {
			case Level::Info: return "INFO";
			case Level::Warning: return "WARN";
			case Level::Error: return "ERROR";
			case Level::Debug: return "DEBUG";
			default: return "UNKNOWN";
		}
	}

	std::string Logger::levelToColor(Level level) {
		switch (level) {
			case Level::Info: return "\033[32m";   // Green
			case Level::Warning: return "\033[33m"; // Yellow
			case Level::Error: return "\033[31m";   // Red
			case Level::Debug: return "\033[36m";   // Cyan
			default: return "\033[0m";
		}
	}

} // namespace GameLib::Utils::Logger
