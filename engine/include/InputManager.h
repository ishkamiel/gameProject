#pragma once

#include "tasks/Task.h"

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

