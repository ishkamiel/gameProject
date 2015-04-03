#include "exceptions/GLEWInitFailedException.h"

#include <GL/glew.h>
#include <sstream>

namespace pdEngine
{

GLEWInitFailedException::GLEWInitFailedException(GLenum& glewError)
{
	std::ostringstream cnvt;
	cnvt << "GLEW initialization error: " << glewGetErrorString(glewError);
	m_what = cnvt.str();
}

GLEWInitFailedException::GLEWInitFailedException(const GLEWInitFailedException& other)
{
	m_what = other.m_what;
}


GLEWInitFailedException::~GLEWInitFailedException()
{}

const char* GLEWInitFailedException::what()
{
	return m_what.c_str();
}

}