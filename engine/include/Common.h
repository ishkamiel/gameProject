#ifndef PDENGINE_GENERAL_H_
#define PDENGINE_GENERAL_H_

#define PD_DELETE(x) if (x != nullptr) delete x

namespace pdEngine
{
#ifdef WIN32 
    constexpr bool win32 = true;
#else
    constexpr bool win32 = false;
#endif /* WIN32 */

    //typedef int long TimeDelta;
}

#endif /* PDENGINE_GENERAL_H_ */
