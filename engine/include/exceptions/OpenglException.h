/* 
 * File:   OpenglException.h
 * Author: ishkamiel
 *
 * Created on April 3, 2015, 4:55 PM
 */

#ifndef OPENGLEXCEPTION_H
#define	OPENGLEXCEPTION_H

#include <GL/glew.h>

#include <stdexcept>
#include <string>

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

#endif	/* OPENGLEXCEPTION_H */

