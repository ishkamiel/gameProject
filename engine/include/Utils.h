#ifndef PDENGINE_UTILS_H_
#define PDENGINE_UTILS_H_

#include "spdlog/spdlog.h"

#include <cassert>
#include <memory>

// #define PD_DELETE(x) if (x != nullptr) delete x

namespace pdEngine
{
#ifdef WIN32 
    constexpr bool win32 = true;
#else
    constexpr bool win32 = false;
#endif /* WIN32 */


    template<typename T> inline void safeDelete(T*& p)
    {
        delete p;
        p = nullptr;
    }

    template<typename T> inline void safeDeleteArray(T*& p)
    {
        delete[] p;
        p = nullptr;
    }

    using Logger = std::shared_ptr<spdlog::logger>;

    inline Logger getLogger()
    {
        static Logger log = spdlog::stderr_logger_mt("pdengine");
        return log;
    }
}

#define DLOG( ... ) getLogger()->debug(__VA_ARGS__)

#ifdef NDEBUG
#undef DLOG
#define DLOG( ... )
#endif /* NDEBUG */

#endif /* PDENGINE_UTILS_H_ */
