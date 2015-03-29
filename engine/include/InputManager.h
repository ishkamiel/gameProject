#ifndef PDENGINE_INPUTMANAGER_H_
#define PDENGINE_INPUTMANAGER_H_

#include "Task.h"

#include <memory>

namespace pdEngine
{
    class InputManager;
    using InputManager_sptr = std::shared_ptr<InputManager>;

    class InputManager : public Task
    {
    public: 
        InputManager();
        virtual ~InputManager();
    protected:
    private:
    };
}








#endif /* PDENGINE_INPUTMANAGER_H_ */
