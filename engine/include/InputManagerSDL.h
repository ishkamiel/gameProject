#ifndef PDENGINE_INPUTMANAGERSDL_H_
#define PDENGINE_INPUTMANAGERSDL_H_

#include "InputManager.h"
#include "events/EventManagerImpl.h"

#include "SDL_events.h"

namespace pdEngine
{

class InputManagerSDL : public InputManager
{
public:
	InputManagerSDL(EventManager_sptr);
	virtual ~InputManagerSDL();
protected:
	void onUpdate(TimeDelta) override;
	void onInit(void) override;
private:

	EventManager_sptr m_EventManager;
	SDL_Event* m_Event;
};

}
#endif /* PDENGINE_INPUTMANAGERSDL_H_ */
