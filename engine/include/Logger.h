#ifndef LOGGER_H_
#define LOGGER_H_

#include "spdlog/spdlog.h"

#include <memory>

namespace pdEngine
{

class pdLogger
{
public:
	pdLogger();
	pdLogger(std::shared_ptr<spdlog::logger>);
	virtual ~pdLogger();

	template<typename... Args>
	inline void debug(const std::string& s, Args&&... args) noexcept
	{
		m_L->debug(s.c_str(), std::forward<Args>(args)...);
	}

	template<typename... Args>
	inline void info(const std::string& s, Args&&... args) noexcept
	{
		m_L->info(s.c_str(), std::forward<Args>(args)...);
	}

	template<typename... Args>
	inline void warn(const std::string& s, Args&&... args) noexcept
	{
		m_L->warn(s.c_str(), std::forward<Args>(args)...);
	}

	template<typename... Args>
	void error(const std::string& s, Args&&... args) noexcept
	{
		m_L->error(s.c_str(), std::forward<Args>(args)...);
	}

private:
	std::shared_ptr<spdlog::logger> m_L;
};

void setLogger(std::shared_ptr<pdLogger>);
void setLogger(std::shared_ptr<spdlog::logger>);
std::shared_ptr<pdLogger> getLogger() noexcept;

}
#define DLOG( ... ) getLogger()->debug(__VA_ARGS__)
#define PD_debug( ... ) getLogger()->debug(__VA_ARGS__)

#ifdef NDEBUG

#define DONT_SET_DEBUG_STUFF
#undef SET_LEVEL_TO_DEBUG
#undef DLOG
#define DLOG( ... )

#undef PD_debug
#define PD_debug( ... )
#endif /* NDEBUG */


#endif /* LOGGER_H_ */
