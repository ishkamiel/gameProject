/*
 * General.h
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#ifndef SOURCE_DIRECTORY__ENGINE_INCLUDES_GENERAL_H_
#define SOURCE_DIRECTORY__ENGINE_INCLUDES_GENERAL_H_

namespace pdEngine
{
#ifdef WIN32 
    constexpr bool win32 = true;
#else
    constexpr bool win32 = false;
#endif /* WIN32 */

    constexpr short MAX_PATH = 100;

	typedef int long TimeDelta;
	typedef unsigned int EventID;
}

#endif /* SOURCE_DIRECTORY__ENGINE_INCLUDES_GENERAL_H_ */
