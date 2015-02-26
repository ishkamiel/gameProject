#include "Task.h"

namespace pdEngine
{
    void ITask::onInit(void)
    {
        state = State::running;
    }

    void ITask::onSuccess(void)
    {}

    void ITask::onFail(void)
    {}

    void ITask::onAbort(void)
    {}
}
