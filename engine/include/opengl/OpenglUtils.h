#pragma once

#include "Logger.h"

#include <epoxy/gl.h>
#include <epoxy/glx.h>

#include <string>

namespace pdEngine
{

inline void fatalOnOpenGLError(const std::string&);
inline void fatalOnShaderCompileError(GLint&);


namespace OpenglUtils
{
std::string getGLLog(const GLuint);
}

/*
 * Definitions
 */

inline void fatalOnShaderCompileError(GLint& ok)
{
	if (ok != GL_TRUE)
	{
        fatal("Failed to compile shader");
	}
}

void fatalOnOpenGLError(const std::string& msg)
{
    const GLenum errorValue = glGetError();

    if (errorValue != GL_NO_ERROR)
    {
        std::string error;

        switch(errorValue) {
            case GL_INVALID_ENUM:
                error = "An unacceptable value is specified for an enumerated argument.";
                break;
            case GL_INVALID_VALUE:
                error = "A numeric argument is out of range.";
                break;
            case GL_INVALID_OPERATION:
                error = "The specified operation is not allowed in the current state.";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "The framebuffer object is not complete.";
                break;
            case GL_OUT_OF_MEMORY:
                error = "There is not enough memory left to execute the command.";
                break;
            case GL_STACK_UNDERFLOW:
                error = "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
                break;
            case GL_STACK_OVERFLOW:
                error = "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
                break;
            default:
                error = "UNKOWN ERROR";
                break;
        }
        fatal("{}: {}", msg, error);
    }
}

}
