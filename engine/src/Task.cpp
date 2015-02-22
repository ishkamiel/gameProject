#include "Task.h"

namespace pdEngine
{
    void Task::onInit(void)
    {
        state = State::running;
    }

    void Task::onSuccess(void)
    {}

    void Task::onFail(void)
    {}

    void Task::onAbort(void)
    {}
}
