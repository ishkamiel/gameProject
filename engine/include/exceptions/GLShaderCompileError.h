#pragma once
#include "Logger.h"
#include "exceptions/InitFailedException.h"

#include <epoxy/gl.h>
#include <epoxy/glx.h>
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

