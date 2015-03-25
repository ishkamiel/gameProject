/*
 * General.h
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#ifndef PDENGINE_GENERAL_H_
#define PDENGINE_GENERAL_H_

#define PD_DELETE(x) if (x != nullptr) delete x

namespace pdEngine
{
#ifdef WIN32 
    // constexpr bool win32 = true;
#else
    // constexpr bool win32 = false;
#endif /* WIN32 */

    // constexpr short MAX_PATH = 100;
    //
	typedef int long TimeDelta;
	//
	// using pdUtils::log;
}

#endif /* PDENGINE_GENERAL_H_ */
