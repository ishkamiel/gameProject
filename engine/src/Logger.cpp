#include "Logger.h"

#include <spdlog/spdlog.h>

#define LOGGER_NAME "pdE"

namespace pdEngine
{

std::string getLoggerName(void) noexcept {
	return LOGGER_NAME;
}

void debug(const std::string& s) noexcept {
	spdlog::get(LOGGER_NAME)->debug(s);
}

void info(const std::string& s) noexcept {
	spdlog::get(LOGGER_NAME)->info(s);
}

void warn(const std::string& s) noexcept {
	spdlog::get(LOGGER_NAME)->warn(s);
}

void error(const std::string& s) noexcept {
	spdlog::get(LOGGER_NAME)->error(s);
}

void fatal(const std::string& s) {
	spdlog::get(LOGGER_NAME)->error(s);
	exit(EXIT_FAILURE);
}

void initLogging() {
	spdlog::stdout_logger_mt( LOGGER_NAME);
	/*
	size_t q_size = 1048576; //queue size must be power of 2
	spdlog::set_async_mode(q_size);
	auto async_file= spd::daily_logger_st("async_file_logger", "logs/async_log.txt");
	async_file->info() << "This is async log.." << "Should be very fast!";
	 */
}

}
