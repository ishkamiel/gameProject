#ifndef PDENGINE_APPLICATIONIMPL_H_
#define PDENGINE_APPLICATIONIMPL_H_

#include "Renderer.h"

#include <SDL.h>

namespace pdEngine
{

    class RendererSDL : public Renderer
    {
        int window_width                { 640 };
        int window_height               { 480 };
        SDL_Window* window              { nullptr };
        SDL_Surface* screenSurface      { nullptr };

    public:
        RendererSDL();
        ~RendererSDL();

        virtual void render(void) override;

    protected:
        virtual void onUpdate(TimeDelta) override;
        virtual void onInit(void) override;

    private:
        bool initSDL();
    };
}


#endif /* PDENGINE_APPLICATIONIMPL_H_ */
