#ifndef LOGGER_H_
#define LOGGER_H_

#include "spdlog/spdlog.h"

namespace pdEngine
{
    using Logger = std::shared_ptr<spdlog::logger>;

    void setLogger(Logger);
    Logger getLogger();
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
