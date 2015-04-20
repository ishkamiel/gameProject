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

	std::string v_getTaskName(void) const noexcept override { return "SDL Input Manager"; }

protected:
	void onUpdate(int deltaMs) noexcept override;
	void onInit(void) noexcept override;
private:

	EventManager_sptr m_EventManager;
	SDL_Event* m_Event;
};

}
