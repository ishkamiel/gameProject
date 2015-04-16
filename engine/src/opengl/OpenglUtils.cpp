#include "opengl/OpenglUtils.h"

#include "Logger.h"

#include <epoxy/gl.h>
#include <epoxy/glx.h>

namespace pdEngine
{
namespace OpenglUtils
{

std::string getGLLog(GLuint const logTarget)
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

    std::string retval{infoLog};
    delete infoLog;
    return retval;
}

}
}