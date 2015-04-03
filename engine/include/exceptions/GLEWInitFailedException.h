/* 
 * File:   SDLInitFailedException.h
 * Author: ishkamiel
 *
 * Created on April 3, 2015, 11:33 AM
 */

#ifndef GLESINITFAILEDEXCEPTION_H_
#define GLESINITFAILEDEXCEPTION_H_

#include "exceptions/InitFailedException.h"

#include <GL/glew.h>

namespace pdEngine
{

class GLEWInitFailedException : public InitFailedException
{
public:
	GLEWInitFailedException(GLenum&);
	GLEWInitFailedException(const GLEWInitFailedException&);
	virtual ~GLEWInitFailedException();
		
	virtual const char* what();	
		
private:
	std::string m_what;
};


}
#endif