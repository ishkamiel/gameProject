#include "Utils.h"

namespace pdEngine
{
    static Logger g_TheLogger;

    void setLogger(Logger logger)
    {
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
        return log;
    }
}
