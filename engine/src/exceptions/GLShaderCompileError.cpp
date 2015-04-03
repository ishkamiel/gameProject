#include "exceptions/GLShaderCompileError.h"

namespace pdEngine {

GLShaderCompileError::GLShaderCompileError(const GLuint logTarget) {
    int length = 0;
    int maxLength = length;

    if (glIsProgram(logTarget)) {
        glGetProgramiv(logTarget, GL_INFO_LOG_LENGTH, &maxLength);
    } else if (glIsShader(logTarget)) {
        glGetShaderiv(logTarget, GL_INFO_LOG_LENGTH, &maxLength);
    } else {
        throw std::logic_error("Unrecognized logTarget");
    }

    m_what = new char[maxLength];

    if (glIsProgram(logTarget)) {
        glGetProgramInfoLog(logTarget, maxLength, &length, m_what);
    } else if (glIsShader(logTarget)) {
        glGetShaderInfoLog(logTarget, maxLength, &length, m_what);
    }
    else
        throw std::logic_error("Unrecognized logTarget");
}

GLShaderCompileError::GLShaderCompileError(const GLShaderCompileError& other) 
{
	m_what = other->m_what;
}

GLShaderCompileError::~GLShaderCompileError() {

    delete m_what;
}

char* GLShaderCompileError::what(void) {
    return m_what;
}

}