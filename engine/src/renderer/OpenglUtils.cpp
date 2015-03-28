#include "renderer/OpenglUtils.h"

#include "Logger.h"

namespace pdEngine
{
    void printGLLog(GLuint const logTarget)
    {
        int length = 0;
        int maxLength = length;

        glGetProgramiv(logTarget, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];

        if (glIsProgram(logTarget))
            glGetProgramInfoLog(logTarget, maxLength, &length, infoLog);
        else if (glIsShader(logTarget))
            glGetShaderInfoLog(logTarget, maxLength, &length, infoLog);
        else
            GET_LOGGER()->warn("Unable to print GLLog for {0}", logTarget);

        if (length > 0) 
        {
            GET_LOGGER()->info(infoLog);
        }

        delete infoLog;
    }
}
