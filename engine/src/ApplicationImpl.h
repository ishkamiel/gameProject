#ifndef PDENGINE_APPLICATIONIMPL_H_
#define PDENGINE_APPLICATIONIMPL_H_

#include <SDL.h>

namespace pdEngine
{

    class ApplicationImpl
    {
    public:
        ApplicationImpl();
        ~ApplicationImpl();

        void init();

    protected:

    private:
        int screen_width = 640;
        int screen_height = 480;

        SDL_Window* window = nullptr;
        SDL_Surface* screenSurface = nullptr;

        void initSDL();
    };
}


#endif /* PDENGINE_APPLICATIONIMPL_H_ */
