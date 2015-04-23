#include "opengl/OpenglUtils.h"

#include "utils/Logger.h"



namespace pdEngine
{

std::string getGLInfoLog(GLuint const logTarget) noexcept
{
    int length = 0;
    int maxLength = length;

    if (glIsProgram(logTarget))
        glGetProgramiv(logTarget, GL_INFO_LOG_LENGTH, &maxLength);
    else if (glIsShader(logTarget))
        glGetShaderiv(logTarget, GL_INFO_LOG_LENGTH, &maxLength);
    else {
        PDE_WARN << "Unrecognized logTarget when trying to retrieve OpenGL InfoLog.";
        return "";
    }

    char* infoLog = new char[maxLength];

    if (glIsProgram(logTarget))
        glGetProgramInfoLog(logTarget, maxLength, &length, infoLog);
    else if (glIsShader(logTarget))
        glGetShaderInfoLog(logTarget, maxLength, &length, infoLog);

    std::string retval{infoLog};
    delete infoLog;
    return retval;
}

}
