/* 
 * File:   OpenglException.h
 * Author: ishkamiel
 *
 * Created on April 3, 2015, 4:55 PM
 */

#ifndef OPENGLEXCEPTION_H
#define	OPENGLEXCEPTION_H


#include <stdexcept>
#include <string>
#include <epoxy/gl.h>
#include <epoxy/glx.h>
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

