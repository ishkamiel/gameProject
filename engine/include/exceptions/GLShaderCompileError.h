/* 
 * File:   GLShaderCompileError.h
 * Author: ishkamiel
 *
 * Created on April 3, 2015, 1:01 PM
 */

#ifndef GLSHADERCOMPILEERROR_H
#define	GLSHADERCOMPILEERROR_H

#include "exceptions/InitFailedException.h"

#include <GL/glew.h>

namespace pdEngine
{

class GLShaderCompileError : public InitFailedException
{
	const std::string m_what;

public:
	GLShaderCompileError(const GLuint);
	GLShaderCompileError(const GLShaderCompileError&);
	virtual ~GLShaderCompileError();

	virtual const char* what();	
};

}
#endif	/* GLSHADERCOMPILEERROR_H */

