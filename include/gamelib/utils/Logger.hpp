#pragma once

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <mutex>
#include <string>

namespace gamelib::utils {

	enum class Level { INFO, WARNING, ERROR, DEBUG };

	class Logger {
	private:
		Logger() {}

		std::ofstream logFile_;
		bool colorEnabled_ = true;
		std::mutex mutex_;

		std::string getTimestamp() {
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

		std::string levelToString(Level level) {
			switch (level) {
				case Level::INFO: return "INFO";
				case Level::WARNING: return "WARN";
				case Level::ERROR: return "ERROR";
				case Level::DEBUG: return "DEBUG";
				default: return "UNKNOWN";
			}
		}

		std::string levelToColor(Level level) {
			switch (level) {
				case Level::INFO: return "\033[32m";   // Green
				case Level::WARNING: return "\033[33m"; // Yellow
				case Level::ERROR: return "\033[31m";   // Red
				case Level::DEBUG: return "\033[36m";   // Cyan
				default: return "\033[0m";
			}
		}
		
	public:
		static Logger& instance() {
			static Logger logger;
			return logger;
		}

		void setLogFile(const std::string& filename) {
			std::lock_guard<std::mutex> lock(mutex_);
			logFile_.open(filename, std::ios::out | std::ios::app);
		}
		void setEnableColor(bool enabled) {
			colorEnabled_ = enabled;
		}
		void log(Level level, const std::string& message) {
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

		void info(const std::string& message) {
			log(Level::INFO, message);
		}

		void warn(const std::string& message) {
			log(Level::WARNING, message);
		}

		void error(const std::string& message) {
			log(Level::ERROR, message);
		}

		void debug(const std::string& message) {
			log(Level::DEBUG, message);
		}
	};
}