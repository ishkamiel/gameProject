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

        bool init();

    protected:

    private:
        int window_width = 640;
        int window_height = 480;

        SDL_Window* window = nullptr;
        SDL_Surface* screenSurface = nullptr;

        bool initSDL();
    };
}


#endif /* PDENGINE_APPLICATIONIMPL_H_ */
