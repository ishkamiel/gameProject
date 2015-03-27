#ifndef PDENGINE_APPLICATIONIMPL_H_
#define PDENGINE_APPLICATIONIMPL_H_

#include "Renderer.h"

#include <SDL.h>
#include <SDL_ttf.h>

namespace pdEngine
{

    class RendererSDL : public Renderer
    {
        int window_width                { 640 };
        int window_height               { 480 };
        std::string windowTitle         { "pdEngine" };

        SDL_Window* window              { nullptr };
        SDL_Surface* screenSurface      { nullptr };

        bool debugPrint                 { true };
        std::string debugString         { "" };
        TTF_Font*                       debugFont;

    public:
        RendererSDL(std::string = "pdEngine");
        ~RendererSDL();

        virtual void render(void) override;
        virtual void printDebugMsg(std::string) override;

    protected:
        virtual void onUpdate(TimeDelta) override;
        virtual void onInit(void) override;

    private:
        bool initSDL();
    };
}


#endif /* PDENGINE_APPLICATIONIMPL_H_ */
