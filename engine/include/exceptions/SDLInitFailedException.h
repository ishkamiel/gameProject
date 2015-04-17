#pragma once

#include "exceptions/InitFailedException.h"

namespace pdEngine
{

class SDLInitFailedException : public InitFailedException
{

public:
	SDLInitFailedException(std::string str);
	SDLInitFailedException(const SDLInitFailedException&);
	virtual ~SDLInitFailedException();

	virtual const char* what() override;	
private:

	std::string m_what;
};

}
