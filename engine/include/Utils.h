#ifndef PDENGINE_UTILS_H_
#define PDENGINE_UTILS_H_

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

}

#endif /* PDENGINE_UTILS_H_ */
