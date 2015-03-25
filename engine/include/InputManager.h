#ifndef PDENGINE_INPUTMANAGER_H_
#define PDENGINE_INPUTMANAGER_H_

#include "EventManager.h"
#include "Task.h"
#include <memory>

namespace pdEngine
{
    class InputManager;
    using InputManager_sptr = std::shared_ptr<InputManager>;

    class InputManager : public Task
    {
    public: 
        InputManager() =delete;
        InputManager(EventManager_sptr);
        virtual ~InputManager();
    protected:
        void onUpdate(TimeDelta) override;
        void onInit(void) override;
        // void onSuccess(void) override;
        // void onFail(void) override;
        // void onAbort(void) override;
    private:
        EventManager_sptr eventManager;
    };
}








#endif /* PDENGINE_INPUTMANAGER_H_ */
