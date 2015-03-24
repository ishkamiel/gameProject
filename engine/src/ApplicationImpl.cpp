#include "ApplicationImpl.h"

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

        // if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        // {
        //
        // }
    }
}
