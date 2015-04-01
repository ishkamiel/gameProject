#ifndef PDENGINE_UTILS_H_
#define PDENGINE_UTILS_H_

#ifdef WIN32 
#define PDENGINE_WIN32 true
#else
#define PDENGINE_WIN32 false
#endif /* WIN32 */

#include <memory>

namespace pdEngine
{
    constexpr bool win32 = PDENGINE_WIN32;

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


}

#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif

#endif /* PDENGINE_UTILS_H_ */
