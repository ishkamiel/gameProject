#include "exceptions/SDLInitFailedException.h"

#include <SDL.h>

#include <sstream>

namespace pdEngine
{

SDLInitFailedException::SDLInitFailedException(std::string str)
{
	std::ostringstream ss;
	ss << str << ", SDL Error: " << SDL_GetError();
	m_what = ss.str();
}

SDLInitFailedException::SDLInitFailedException(const SDLInitFailedException& other)
{
	m_what = other.m_what;
}

SDLInitFailedException::~SDLInitFailedException()
{}

const char* SDLInitFailedException::what()
{
	return m_what.c_str();
}

}