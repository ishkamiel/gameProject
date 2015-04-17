#pragma once

#include <stdexcept>

namespace pdEngine
{

class InitFailedException : public std::runtime_error
{
public:

    InitFailedException() : std::runtime_error("InitFailedException")
    {
    }

    virtual ~InitFailedException()
    {
    };
    virtual const char* what() = 0;
};

}
