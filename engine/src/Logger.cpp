#include "Logger.h"

#include <cassert>

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

}
