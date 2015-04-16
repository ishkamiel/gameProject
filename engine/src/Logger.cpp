#include "Logger.h"

#include <spdlog/spdlog.h>

namespace pdEngine
{

constexpr char* s_LoggerName = { "PDE" };

std::string getLoggerName(void) noexcept {
	return s_LoggerName;
}

std::ostream debug(void) noexcept {
	return spdlog::getLogger(s_LoggerName)->debug();
}

std::ostream info(void) noexcept {
	return spdlog::getLogger(s_LoggerName)->info();
}

std::ostream warn(void) noexcept {
	return spdlog::getLogger(s_LoggerName)->warn();
}

std::ostream error(void) noexcept {
	return spdlog::getLogger(s_LoggerName)->error();
}

};
