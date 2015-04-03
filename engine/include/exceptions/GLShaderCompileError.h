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
public:
	GLShaderCompileError() =delete;
	GLShaderCompileError(const GLuint);
	GLShaderCompileError(const GLShaderCompileError&);
	virtual ~GLShaderCompileError();

	virtual const char* what();	

private:
	std::string m_what;
};

}
#endif	/* GLSHADERCOMPILEERROR_H */

