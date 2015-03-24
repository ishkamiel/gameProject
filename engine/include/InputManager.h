#ifndef PDENGINE_INPUTMANAGER_H_
#define PDENGINE_INPUTMANAGER_H_

#include "EventManager.h"
#include <memory>

namespace pdEngine
{
    class InputManager;
    using InputManager_sptr = std::shared_ptr<InputManager>;

    class InputManager
    {
    public: 
        //InputManager() =delete;
        InputManager(EventManager_sptr);
        virtual ~InputManager();
    protected:
    private:
    };
}








#endif /* PDENGINE_INPUTMANAGER_H_ */
