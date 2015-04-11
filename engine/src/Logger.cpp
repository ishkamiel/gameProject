#include "Logger.h"
#include "spdlog/spdlog.h"

namespace pdEngine
{
static std::shared_ptr<pdLogger> g_TheLogger;


pdLogger::pdLogger()
	: m_L(spdlog::rotating_logger_mt("default_logger", "log", 1048576 * 5, 3))
{
#ifndef DONT_SET_DEBUG_STUFF
	m_L->set_level(spdlog::level::debug);
#endif
}

pdLogger::pdLogger(std::shared_ptr<spdlog::logger> l)
: m_L(l)
{}

pdLogger::~pdLogger() = default;

void setLogger(std::shared_ptr<pdLogger> logger)
{
	g_TheLogger = logger;
}

void setLogger(std::shared_ptr<spdlog::logger> l)
{
	g_TheLogger.reset(new pdLogger(l));
}

std::shared_ptr<pdLogger> getLogger() noexcept
{
	if (!g_TheLogger)
	{
		g_TheLogger.reset(new pdLogger());
	}

	return g_TheLogger;
}

}
