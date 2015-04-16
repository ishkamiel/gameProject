#pragma once

#include <memory>
#include <ostream>
#include <sstream>
#include <iostream>

namespace pdEngine {

std::string getLoggerName(void) noexcept;

void debug(const std::string&) noexcept;
void info(const std::string&) noexcept;
void warn(const std::string&) noexcept;
void error(const std::string&) noexcept;
void fatal(const std::string&);

void initLogging();

template<typename T>
static inline void logToStream(std::stringstream& o, T&& t) noexcept {
	o << t << std::endl;
}

template<typename T, typename... Args>
static inline void logToStream(std::stringstream& o, T&& t, Args&&... args) noexcept {
	logToStream(o, std::forward<T>(t));
	logToStream(o, std::forward<Args>(args)...);
}

template<typename... Args>
static inline std::string stringify(const std::string &s, Args&&... args) noexcept {
	std::cerr << "Gonna stringify me some strings";
	std::stringstream ss;
	ss << s;
	logToStream(ss, std::forward<Args>(args)...);
	std::cerr << "Done whith that: " << ss.str() << "\n";
	return ss.str();
}

template<typename... Args>
inline void debug(const std::string &s, Args &&... args) noexcept {
	debug(stringify(s, std::forward<Args>(args)...));
}

template<typename... Args>
inline void info(const std::string &s, Args &&... args) noexcept {
	std::cerr << "here wer are\n";
	info(stringify(s, std::forward<Args>(args)...));
}

template<typename... Args>
inline void warn(const std::string &s, Args &&... args) noexcept {
	warn(stringify(s, std::forward<Args>(args)...));
}

template<typename... Args>
void error(const std::string &s, Args &&... args) noexcept {
	error(stringify(s, std::forward<Args>(args)...));
}

template<typename... Args>
void fatal(const std::string &s, Args &&... args) noexcept {
	fatal(stringify(s, std::forward<Args>(args)...));
}

}

#define PD_debug( ... ) debug(__VA_ARGS__)

#ifdef NDEBUG

#define DONT_SET_DEBUG_STUFF
#undef SET_LEVEL_TO_DEBUG
#undef DLOG
#define DLOG( ... )

#undef PD_debug
#define PD_debug( ... )
#endif /* NDEBUG */
