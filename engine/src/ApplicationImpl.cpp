#include "ApplicationImpl.h"
#include "Logger.h"

#include <SDL.h>

namespace pdEngine 
{
    ApplicationImpl::ApplicationImpl() 
    {
    }

    ApplicationImpl::~ApplicationImpl()
    {
    }

    void ApplicationImpl::init()
    {
        initSDL();
    }

    void ApplicationImpl::initSDL()
    {
        auto logger = LOGGER;
        logger->debug("Initializing SDL");

        if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        {
            logger->error("SDL_Init error: {}", 1);
            logger->error() << SDL_GetError() << 1;
            exit(-1);
        }
    }
}
