#ifndef PDENGINE_LOGGER_H_
#define PDENGINE_LOGGER_H_

#include "spdlog/spdlog.h"

#define MK_LOGGER() spdlog::stderr_logger_mt("pdengine")
#define GET_LOGGER() spdlog::get("pdengine")
#define LOGGER_SET_DEBUG(l) l->set_level(spdlog::level::debug)

#define DLOG( ... ) spdlog::get("pdengine")->debug(__VA_ARGS__)

#ifdef NDEBUG

#undef DLOG
#define DLOG( ... )

#endif /* NDEBUG */

#endif /* PDENGINE_LOGGER_H_ */
