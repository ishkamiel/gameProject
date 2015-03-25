#include "InputManager.h"

namespace pdEngine 
{
    InputManager::InputManager(EventManager_sptr)
    {
    }

    InputManager::~InputManager()
    {
    }

    void InputManager::onUpdate(TimeDelta delta)
    {
        // TODO
        (void)delta;
    }

    void InputManager::onInit(void) 
    {
        // TODO setup sdl event stuff here
    }
}
