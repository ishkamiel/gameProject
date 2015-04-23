#pragma once

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace pdEngine {

enum class LogLevel : unsigned short
{
	all = 0,
	trace,
	debug,
	info,
	warn,
	error,
	fatal
};

void setGlobalLogLevel(LogLevel) noexcept;

}

#define PDE_TRACE BOOST_LOG_TRIVIAL(trace)
#define PDE_DEBUG BOOST_LOG_TRIVIAL(debug)
#define PDE_INFO BOOST_LOG_TRIVIAL(info)
#define PDE_WARN BOOST_LOG_TRIVIAL(warning)
#define PDE_ERROR BOOST_LOG_TRIVIAL(error)
#define PDE_FATAL BOOST_LOG_TRIVIAL(fatal)
