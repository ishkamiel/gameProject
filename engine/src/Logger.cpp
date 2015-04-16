#include "Logger.h"

#include <spdlog/spdlog.h>

namespace pdEngine
{

static const std::string s_LoggerName = "pdE" ;

std::string getLoggerName(void) noexcept {
	return s_LoggerName;
}

void debug(const std::string& s) noexcept {
	spdlog::get(s_LoggerName)->debug(s);
}

void info(const std::string& s) noexcept {
	spdlog::get(s_LoggerName)->info(s);
}

void warn(const std::string& s) noexcept {
	spdlog::get(s_LoggerName)->warn(s);
}

void error(const std::string& s) noexcept {
	spdlog::get(s_LoggerName)->error(s);
}

void fatal(const std::string& s) {
	spdlog::get(s_LoggerName)->error(s);
	exit(EXIT_FAILURE);
}

}
