#pragma once

#include "InputManager.h"
#include "events/EventManagerImpl.h"

#include "SDL2/SDL_events.h"

namespace pdEngine
{

class InputManagerSDL : public InputManager
{
public:
	InputManagerSDL(EventManager_sptr);
	virtual ~InputManagerSDL();
protected:
	void onUpdate(const TimeDelta&) noexcept override;
	void onInit(void) noexcept override;
private:

	EventManager_sptr m_EventManager;
	SDL_Event* m_Event;
};

}
