#include "renderer/SDLRenderer.h"

#include "Utils.h"

namespace pdEngine
{
    SDLRenderer::SDLRenderer(std::string windowTitle)
        : windowTitle(windowTitle)
    {
    }

    SDLRenderer::~SDLRenderer()
    {
        if (window != nullptr)
            SDL_DestroyWindow(window);

        SDL_Quit();
    }

    void SDLRenderer::onInit(void)
    {
        auto log = getLogger();
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

        std::string fontFile = "/usr/share/texlive/texmf-dist/fonts/truetype/public/opensans/OpenSans-Regular.ttf";
        debugFont = TTF_OpenFont(fontFile.c_str(), 24);
        if (debugFont == nullptr)
        {
            log->error("SDL TTF_OpenFont() failed: {0}", TTF_GetError());
            return fail();
        }

        debugPosition = new SDL_Rect();
        debugPosition->x = 0;
        debugPosition->y = 0;
    }

    void SDLRenderer::onUpdate(TimeDelta delta)
    {
        std::stringstream sstm;
        sstm << "delta: " << delta;
        debugPosition->x = (debugPosition->x + 1)%window_width;
        debugPosition->y = (debugPosition->y + 1)%window_height;
        printDebugMsg(sstm.str().c_str());
    }

    void SDLRenderer::render(void) const
    {
        SDL_FillRect( screenSurface, nullptr, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
        if (debugMessage != nullptr)
        {
            SDL_BlitSurface(debugMessage, nullptr, screenSurface, debugPosition);
        }
        SDL_UpdateWindowSurface( window );
    }

    void SDLRenderer::printDebugMsg(std::string msg)
    {
        if (debugPrint)
        {
            SDL_Color text_color {150, 0, 50, 0};

            debugMessage = TTF_RenderText_Solid(debugFont,
                    msg.c_str(),
                    text_color);

            if (debugMessage == nullptr)
            {
                getLogger()->error("TTF_RenderText_Solid failed: {0}", TTF_GetError());
                TTF_Quit();
                SDL_Quit();
                exit(1);
            }
        }
    }
}
