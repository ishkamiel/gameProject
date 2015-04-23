#include "exceptions/OpenglException.h"

#include "opengl/OpenglUtils.h"

#include <sstream>

namespace pdEngine
{

OpenglException::OpenglException(std::string str)
: std::runtime_error("OpenglException"), m_what(str)
{
}

OpenglException::OpenglException(const GLuint logTarget)
: std::runtime_error("OpenglException")
{
    std::ostringstream cnvt;
    cnvt << "Shader compile error: " << getGLInfoLog(logTarget);
    m_what = cnvt.str();
}

OpenglException::OpenglException(const OpenglException& other)
: std::runtime_error("OpenglException")
{
    m_what = other.m_what;
}

OpenglException::~OpenglException()
{
}

const char* OpenglException::what(void)
{
    return m_what.c_str();
}

}