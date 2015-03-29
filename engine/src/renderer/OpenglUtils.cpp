#include "renderer/OpenglUtils.h"

#include "Logger.h"

namespace pdEngine
{
    void printGLLog(GLuint const logTarget)
    {
        int length = 0;
        int maxLength = length;

        if (glIsProgram(logTarget))
            glGetProgramiv(logTarget, GL_INFO_LOG_LENGTH, &maxLength);
        else if (glIsShader(logTarget))
            glGetShaderiv(logTarget, GL_INFO_LOG_LENGTH, &maxLength);
        else
            throw std::logic_error("Unrecognized logTarget");

        char* infoLog = new char[maxLength];

        if (glIsProgram(logTarget))
            glGetProgramInfoLog(logTarget, maxLength, &length, infoLog);
        else if (glIsShader(logTarget))
            glGetShaderInfoLog(logTarget, maxLength, &length, infoLog);
        else
            throw std::logic_error("Unrecognized logTarget");

        if (length > 0) 
        {
            GET_LOGGER()->info("gl{0}InfoLog: {1}", (
                        glIsProgram(logTarget) ? "Program" :
                        (glIsShader(logTarget) ? "Shader" : 
                         "UNKNOWN")), infoLog);
        }
        else 
        {
            GET_LOGGER()->warn("fetched glInfoLog seems to be empty for {0}", logTarget);
        }

        delete infoLog;
    }

    bool setGLAttribute(const SDL_GLattr attr, const int value)
    {
        if (SDL_GL_SetAttribute(attr, value) != 0) 
        {
            GET_LOGGER()->warn("Error  setting GL attirbute. SDL Error: {0}", SDL_GetError());
            return false;
        }
        return true;
    }
}
