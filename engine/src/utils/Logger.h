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
	fatal,
	none
};
void setGlobalLogLevel(LogLevel) noexcept;

void printEngineBuildInfo(std::ostream &os) noexcept;
void printStackTrace(void) noexcept;
void printStackTrace(int sig) noexcept;

}

#define PDE_TRACE BOOST_LOG_TRIVIAL(trace)
#define PDE_DEBUG BOOST_LOG_TRIVIAL(debug)
#define PDE_INFO BOOST_LOG_TRIVIAL(info)
#define PDE_WARN BOOST_LOG_TRIVIAL(warning)
#define PDE_ERROR BOOST_LOG_TRIVIAL(error)
#define PDE_FATAL BOOST_LOG_TRIVIAL(fatal)

#define PDE_EXIT_FAILURE(message) \
    PDE_FATAL << message << ", at [" << __FILE__ << ":" << __LINE__ << "]"; \
    std::cerr << message << ", at [" << __FILE__ << ":" << __LINE__ << "]"; \
    printStackTrace(); \
	exit(EXIT_FAILURE);

#define PDE_NOT_IMPLEMENTED_FATAL() PDE_EXIT_FAILURE("not implemented");

// #define QUOTE(x) "x"
#define PDE_ASSERT(check, message) \
    if (!(check)) { PDE_EXIT_FAILURE(message);}

#ifdef NDEBUG
#undef PDE_ASSERT
#define PDE_ASSERT(check, message)
#endif /* NDEBUG */

