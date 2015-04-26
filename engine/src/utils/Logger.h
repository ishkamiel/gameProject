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

#define PDE_NOT_IMPLEMENTED_FATAL() \
	PDE_FATAL << "not implemeneted [" << __FILE__ << ":" << __LINE__ << "]"; \
	exit(EXIT_FAILURE);

#define QUOTE(x) "x"
#define PDE_ASSERT(check, message) \
	if (!(check)) {\
        PDE_FATAL << message << ", on[" << __FILE__ << ":" << __LINE__<< "]";\
        exit(EXIT_FAILURE);}

#ifdef NDEBUG
#undef PDE_ASSERT
#define PDE_ASSERT(check, message)
#endif /* NDEBUG */

