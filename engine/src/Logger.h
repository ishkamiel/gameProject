#ifndef PDENGINE_LOGGER_H_
#define PDENGINE_LOGGER_H_

#include "spdlog/spdlog.h"

#define MK_LOGGER() spdlog::stderr_logger_mt("pdengine")
#define GET_LOGGER() spdlog::get("pdengine")
#define LOGGER_SET_DEBUG(l) l->set_level(spdlog::level::debug)

#ifndef NDEBUG
#undef LOG_DEBUG
#define LOG_DEBUG spdlog::get("pdengine")->debug()
#endif

#endif /* PDENGINE_LOGGER_H_ */
