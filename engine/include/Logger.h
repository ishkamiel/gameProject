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

#ifdef NDEBUG
#undef DLOG
#define DLOG( ... )
#endif /* NDEBUG */

#endif /* LOGGER_H_ */
