#include "RendererSDL.h"
#include "Logger.h"

#include <SDL.h>
#include <SDL_ttf.h>

namespace pdEngine
{
    RendererSDL::RendererSDL(std::string windowTitle)
        : windowTitle(windowTitle)
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
        auto log = GET_LOGGER();
        if (!isUninitialized()) throw std::string("duplicate initializations");

        log->debug("Initializing SDL");

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            log->error("SDL_Init error: {0}", SDL_GetError());
            return fail();
        }

        window = SDL_CreateWindow(windowTitle.c_str(),
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                window_width, window_height,
                SDL_WINDOW_SHOWN);

        if (window == nullptr)
        {
            log->error("SDL_CreateWindow Error: {0}", SDL_GetError());
            return fail();
        }

        screenSurface = SDL_GetWindowSurface(window);

        if (TTF_Init() != 0) 
        {
            log->error("SDL TTF_init failed: {0}", TTF_GetError());
            return fail();
        }

        // Load a font
        TTF_Font *font;
        font = TTF_OpenFont("FreeSans.ttf", 24);
        if (font == NULL)
        {
            log->error("SDL TTF_OpenFont() failed: {0}", TTF_GetError());
            return fail();
        }
    }

    void RendererSDL::onUpdate(TimeDelta delta)
    {
        (void)delta;
    }

    void RendererSDL::render()
    {
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
        SDL_UpdateWindowSurface( window );
    }

    void RendererSDL::printDebugMsg(std::string msg)
    {
        if (debugPrint)
        {
            debugString = msg;
        }
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

        window = SDL_CreateWindow(windowTitle.c_str(),
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

        return true;
    }
}
