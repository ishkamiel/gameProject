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

    void InputManagerSDL::onUpdate(const TimeDelta& delta) noexcept
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

    void InputManagerSDL::onInit(void) noexcept
    {
        // TODO setup sdl event stuff here?
    }
}
