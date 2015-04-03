/* 
 * File:   InitFailedException.h
 * Author: ishkamiel
 *
 * Created on April 3, 2015, 11:26 AM
 */

#ifndef INITFAILEDEXCEPTION_H
#define	INITFAILEDEXCEPTION_H

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
#endif	/* INITFAILEDEXCEPTION_H */