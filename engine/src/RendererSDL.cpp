#include "RendererSDL.h"
#include "Logger.h"

#include <SDL.h>

namespace pdEngine
{
    RendererSDL::RendererSDL()
    {
    }

    RendererSDL::~RendererSDL()
    {
        if (window != nullptr)
            SDL_DestroyWindow(window);

        SDL_Quit();
    }

    void RendererSDL::onInit(void)
    {
        if (isUninitialized()) 
        {
            if (!initSDL())
                fail();
        }
    }

    void RendererSDL::onUpdate(TimeDelta delta)
    {
        (void)delta;
    }

    void RendererSDL::render()
    {
        // TODO
    }


    bool RendererSDL::initSDL()
    {
        auto logger = GET_LOGGER();
        logger->debug("Initializing SDL");

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            logger->error("SDL_Init error: {}", 1);
            logger->error() << SDL_GetError() << 1;
            return false;
        }

        window = SDL_CreateWindow("Hello World!",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                window_width, window_height,
                SDL_WINDOW_SHOWN);

        if (window == nullptr)
        {
            logger->error("SDL_CreateWindow Error: {}", 1);
            logger->error() << SDL_GetError() << 1;
            return false;
        }

        screenSurface = SDL_GetWindowSurface(window);
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
        SDL_UpdateWindowSurface( window );

        return true;
    }
}
