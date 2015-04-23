#include "exceptions/GLShaderCompileError.h"

#include "opengl/OpenglUtils.h"

#include <string>
#include <sstream>

namespace pdEngine {

GLShaderCompileError::GLShaderCompileError(const GLuint logTarget) {
	std::ostringstream cnvt;
	cnvt << "Shader compile error: " << getGLInfoLog(logTarget);
	m_what = cnvt.str();
}

GLShaderCompileError::GLShaderCompileError(const GLShaderCompileError& other) 
{
    m_what = other.m_what;
}

GLShaderCompileError::~GLShaderCompileError(void)
{}


const char* GLShaderCompileError::what(void) {
    return m_what.c_str();
}

}