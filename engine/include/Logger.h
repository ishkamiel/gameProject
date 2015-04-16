#pragma once

#include <memory>
#include <ostream>

namespace pdEngine {

std::ostream debug(void) noexcept;

std::ostream info(void) noexcept;

std::ostream warn(void) noexcept;

std::ostream error(void) noexcept;

std::string getLoggerName(void) noexcept;

template<typename T>
static inline void logToStream(std::ostream &o, T& t) noexcept {
	o << t << std::endl;
}

template<typename T, typename... Args>
static inline void logToStream(std::ostream &o, T& t, Args&&... args) noexcept {
	logToStream(o, t);
	logToStream(o, args...);
}

template<typename... Args>
inline void debug(const std::string &s, Args &&... args) noexcept {
	logToStream(debug(), s, std::forward<Args>(args)...);
}

template<typename... Args>
inline void info(const std::string &s, Args &&... args) noexcept {
	//TODO: m_L->info(s.c_str(), std::forward<Args>(args)...);
}

template<typename... Args>
inline void warn(const std::string &s, Args &&... args) noexcept {
	//TODO: m_L->warn(s.c_str(), std::forward<Args>(args)...);
}

template<typename... Args>
void error(const std::string &s, Args &&... args) noexcept {
	//TODO: m_L->error(s.c_str(), std::forward<Args>(args)...);
}

template<typename... Args>
void fatal(const std::string &s, Args &&... args) noexcept {
	//TODO: m_L->error(s.c_str(), std::forward<Args>(args)...);
	exit(EXIT_FAILURE);
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
