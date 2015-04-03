#include "exceptions/GLShaderCompileError.h"

#include <string>

/*
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

    char* what = new char[maxLength];

    if (glIsProgram(logTarget)) {
        glGetProgramInfoLog(logTarget, maxLength, &length, what);
    } else if (glIsShader(logTarget)) {
        glGetShaderInfoLog(logTarget, maxLength, &length, what);
    } else
        throw std::logic_error("Unrecognized logTarget");
	
	std::ostringstream cnvt;
	cnvt << "Shader compile error: " << what;
	m_what = cnvt.str();
}

GLShaderCompileError::GLShaderCompileError(const GLShaderCompileError& other) 
{
    //m_what = other.m_what;
}

GLShaderCompileError::~GLShaderCompileError() 
{}


const char* GLShaderCompileError::what(void) {
    return m_what.c_str();
}

}*/