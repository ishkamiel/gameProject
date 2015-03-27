#include "InputManagerSDL.h"

namespace pdEngine 
{
    InputManagerSDL::InputManagerSDL(EventManager_sptr em)
        : eventManager(em), event(new SDL_Event())
    {
		assert (event != nullptr);
		assert (eventManager);
	}

    InputManagerSDL::~InputManagerSDL()
    {
        delete event;
    }

    void InputManagerSDL::onUpdate(TimeDelta delta)
    {
        (void) delta;
		
		assert(eventManager);

        while (SDL_PollEvent(event) != 0)
        {
            if (event->type == SDL_QUIT)
            {
                eventManager->queueEvent(ev_RequestQuit);
            }
        }
    }

    void InputManagerSDL::onInit(void) 
    {
        // TODO setup sdl event stuff here?
    }
}
