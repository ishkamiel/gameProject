#include "Logger.h"

namespace pdEngine
{
    static Logger g_TheLogger;

    void setLogger(Logger logger)
    {
		assert(g_TheLogger == nullptr);
        g_TheLogger = logger;
    }

    Logger getLogger()
    {
        if (g_TheLogger)
        {
            return g_TheLogger;
        }
        static Logger log = spdlog::rotating_logger_mt("default_logger", 
                "log", 1048576 * 5, 3);

#ifndef DONT_SET_DEBUG_STUFF
        log->set_level(spdlog::level::debug);
#endif
        return log;
    }
}
