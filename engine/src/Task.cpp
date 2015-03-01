#include "Task.h"

namespace pdEngine
{
    Task::~Task() {}

    void Task::onInit(void)
    {
        state = TaskState::running;
    }

    void Task::onSuccess(void)
    {}

    void Task::onFail(void)
    {}

    void Task::onAbort(void)
    {}

    void Task::AttachChild(Task_sptr child)
    {
        childTask = child;
    }

    Task_sptr Task::removeChild(void)
    {
        auto retval = childTask;
        childTask = nullptr;

        return retval;
    }

    Task_sptr Task::peekChild(void)
    {
        return childTask;
    }
}
