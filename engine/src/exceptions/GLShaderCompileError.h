#pragma once

#include "exceptions/InitFailedException.h"

#include <epoxy/gl.h>
#include <epoxy/glx.h>
namespace pdEngine
{

class GLShaderCompileError : public InitFailedException
{
public:
	GLShaderCompileError(void) =delete;
	GLShaderCompileError(const GLuint);
	GLShaderCompileError(const GLShaderCompileError&);
	virtual ~GLShaderCompileError(void);

	virtual const char* what(void);

private:
	std::string m_what;
};

}

