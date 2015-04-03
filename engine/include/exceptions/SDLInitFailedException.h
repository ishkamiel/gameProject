/* 
 * File:   SDLInitFailedException.h
 * Author: ishkamiel
 *
 * Created on April 3, 2015, 11:33 AM
 */

#ifndef SDLINITFAILEDEXCEPTION_H
#define	SDLINITFAILEDEXCEPTION_H

#include "exceptions/InitFailedException.h"

namespace pdEngine
{

class SDLInitFailedException : public InitFailedException
{

public:
	SDLInitFailedException();
	SDLInitFailedException(const SDLInitFailedException&);
	virtual ~SDLInitFailedException();

	virtual const char* what();	
private:

	const std::string m_what;
};

}
#endif	/* SDLINITFAILEDEXCEPTION_H */

