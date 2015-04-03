#include "exceptions/SDLInitFailedException.h"

#include <SDL.h>

#include <sstream>

namespace pdEngine
{

SDLInitFailedException::SDLInitFailedException(std::string str)
{
	std::ostringstream cnvt;
	cnvt << str << ", SDL Error: " << SDL_GetError();
	m_what = cnvt.str();
}

SDLInitFailedException::SDLInitFailedException(const SDLInitFailedException& other)
{
	//m_what = ohter->m_what;
}

SDLInitFailedException::~SDLInitFailedException()
{}

const char* SDLInitFailedException::what()
{
	return m_what.c_str();
}

}