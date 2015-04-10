#include "InputManagerSDL.h"

namespace pdEngine 
{
    InputManagerSDL::InputManagerSDL(EventManager_sptr em)
        : m_EventManager(em), m_Event(new SDL_Event())
    {
		assert (m_Event != nullptr);
		assert (m_EventManager);
	}

    InputManagerSDL::~InputManagerSDL()
    {
        delete m_Event;
    }

    void InputManagerSDL::onUpdate(TimeDelta delta)
    {
        (void) delta;
		
		assert(m_EventManager);

        while (SDL_PollEvent(m_Event) != 0)
        {
            if (m_Event->type == SDL_QUIT)
            {
                m_EventManager->queueEvent(ev_RequestQuit);
            }
        }
    }

    void InputManagerSDL::onInit(void) 
    {
        // TODO setup sdl event stuff here?
    }
}
