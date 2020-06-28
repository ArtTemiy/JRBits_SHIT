#pragma once
#include <iostream>
#include <fstream>

class Logger {
	std::string name_;
	bool new_line_;
	static bool CONFIG_READ;
	static bool ENABLE_LOGGING;

public:
	Logger(const std::string& name = "") : name_(name), new_line_(true) {
		if (!CONFIG_READ) {
			std::ifstream logger_config("../../logger_ñonfig.config");
			if (!logger_config.is_open()) {
				throw std::runtime_error("Wasn't able to open logger_config.config");
			}
			logger_config >> ENABLE_LOGGING;
			CONFIG_READ = true;
		}
		std::cout << "[LOGGER CONFIGURATION \"" + name + "\"]: ";
		std::cout << "\t ENABLE_LOGGING: " << ENABLE_LOGGING << std::endl;
	}
	/*Logger(const Logger& other) {
		name_ = other.name_;
		is_reference_ = 1;
	}*/

	template <class T>
	Logger& operator<<(const T& var) {
		if (Logger::ENABLE_LOGGING) {
			if (new_line_) {
				std::cout << "[" << name_ << "] ";
				new_line_ = false;
			}
			std::cout << var;
		}
		return *this;
	}

	Logger& operator<<(std::ostream& (*f)(std::ostream&)) {
		if (Logger::ENABLE_LOGGING) {
			if (new_line_) {
				std::cout << "[" << name_ << "] ";
				new_line_ = false;
			}
			std::cout << f;
		}
		new_line_ = true;

		return *this;
	}
};