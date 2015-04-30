#include "utils/Logger.h"

#include "build_options.h"

#include <execinfo.h>

namespace pdEngine
{

void setGlobalLogLevel(LogLevel level) noexcept
{
	auto boostLevel = boost::log::trivial::fatal;

	switch (level) {
		case LogLevel::all:
		case LogLevel::trace:
			boostLevel = boost::log::trivial::trace;
			break;
		case LogLevel::debug:
			boostLevel = boost::log::trivial::debug;
	        break;
		case LogLevel::info:
			boostLevel = boost::log::trivial::info;
	        break;
		case LogLevel::warn:
			boostLevel = boost::log::trivial::warning;
	        break;
		case LogLevel::error:
			boostLevel = boost::log::trivial::error;
	        break;
		case LogLevel::fatal:
			boostLevel = boost::log::trivial::fatal;
	        break;
	}


	boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= boostLevel
    );
}

void printEngineBuildInfo(std::ostream &os) noexcept
{
	os << PDE_BUILDOPT_ENGINE_NAME;
	os << " v" << PDE_BUILDOPT_ENGINE_VERSION;
	os << " (" << PDE_BUILDOPT_BUILD_TYPE << " build)" << std::endl;
}

void printStackTrace(void) noexcept
{
	std::cerr << "running: ";
	printEngineBuildInfo(std::cerr);

	void *array[10];
	auto size = backtrace(array, 10);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
}

void printStackTrace(int sig) noexcept
{
	std::cerr << "Error: signal " << sig << std::endl;
	printStackTrace();
}

}
