#pragma once

#include "utils/Logger.h"

#include <epoxy/gl.h>
#include <epoxy/glx.h>

#include <string>

namespace pdEngine
{

/**
 * @brief check for OpenGL errors, and quit on error.
 */
inline void fatalOnOpenGLError(const std::string&) noexcept;

/**
 * @brief Retrieve InfoLog for OpenGL error.
 */
std::string getGLInfoLog(const GLuint) noexcept;

/***************************************************************************************************
 * Definitions...
 */

void fatalOnOpenGLError(const std::string& msg) noexcept
{
    //GLenum errno = glGetError();
    const GLenum errorValue = glGetError();

    if (errorValue != GL_NO_ERROR) {
        std::string error;

        switch (errorValue) {
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

        PDE_FATAL << msg << " (error value: " << errorValue << ") " << error;
        exit(EXIT_FAILURE);
    }
}

}
