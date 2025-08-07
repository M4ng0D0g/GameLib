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

	enum class Level {
		DEBUG, INFO, WARNING, ERROR
	};

	class Logger {
	public:
		static Logger& instance() {
			static Logger logger;
			return logger;
		}

		// --------------------------------------------------------------------------------

		void setLogFile(const std::string& filename) {
			std::lock_guard<std::mutex> lock(mutex_);
			logFile_.open(filename, std::ios::out | std::ios::app);
		}

		void setColorEnabled(bool enabled) {
			colorEnabled_ = enabled;
		}

		void setConsoleEnabled(bool enabled) {
			consoleEnabled_ = enabled;
		}

		void setLogLevel(Level level) {
			logLevel_ = level;
		}

		// --------------------------------------------------------------------------------

		void info(const std::string& message) {
			if (logLevel_ <= Level::INFO) log(Level::INFO, message);
		}

		void warn(const std::string& message) {
			if (logLevel_ <= Level::WARNING) log(Level::WARNING, message);
		}

		void error(const std::string& message) {
			if (logLevel_ <= Level::ERROR) log(Level::ERROR, message);
		}

		void debug(const std::string& message) {
			if (logLevel_ <= Level::DEBUG) log(Level::DEBUG, message);
		}

	private:
		Logger() {}
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		// --------------------------------------------------------------------------------

		std::ofstream logFile_;
		bool colorEnabled_{true};
		bool consoleEnabled_{true};
		Level logLevel_{Level::INFO};

		std::mutex mutex_;

		// --------------------------------------------------------------------------------

		void log(Level level, const std::string& message) {
			std::lock_guard<std::mutex> lock(mutex_);

			std::string timestamp = getTimestamp();
			std::string levelStr = levelToString(level);
			std::string color = colorEnabled_ ? levelToColor(level) : "";

			std::string formatted = "[" + timestamp + "] [" + levelStr + "] " + message;

			// Console output
			if(consoleEnabled_) {
				if (colorEnabled_) {
					std::cout << color << formatted << "\033[0m" << std::endl;
				} else {
					std::cout << formatted << std::endl;
				}
			}
			
			// File output
			if (logFile_.is_open()) {
				logFile_ << formatted << std::endl;
			}
		}

		// --------------------------------------------------------------------------------

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
	};
}