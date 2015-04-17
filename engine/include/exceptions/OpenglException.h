#pragma once

#include "opengl/Epoxy.h"

#include <stdexcept>

namespace pdEngine
{

class OpenglException : public std::runtime_error
{
public:
    OpenglException() = delete;
    OpenglException(std::string);
    OpenglException(const GLuint);
    OpenglException(const OpenglException&);
    virtual ~OpenglException();
    virtual const char* what();
private:
    std::string m_what;
};

}

