#ifndef PDENGINE_APPLICATIONIMPL_H_
#define PDENGINE_APPLICATIONIMPL_H_

#include "renderer/Renderer.h"

#include <SDL.h>
#include <SDL_ttf.h>

namespace pdEngine
{

    class SDLRenderer : public Renderer
    {
        int window_width                { 640 };
        int window_height               { 480 };
        std::string windowTitle         { "pdEngine" };

        SDL_Window* window              { nullptr };
        SDL_Surface* screenSurface      { nullptr };

        bool debugPrint                 { true };
        std::string debugString         { "" };
        TTF_Font*                       debugFont;
        SDL_Surface*                    debugMessage;
        SDL_Rect*                       debugPosition;

    public:
        SDLRenderer(std::string = "pdEngine");
        ~SDLRenderer();

        virtual void render(void) override;
        virtual void printDebugMsg(std::string) override;

    protected:
        virtual void onUpdate(TimeDelta) override;
        virtual void onInit(void) override;

    private:
        // bool initSDL();
    };
}


#endif /* PDENGINE_APPLICATIONIMPL_H_ */
