#include "tasks/Task.h"

namespace pdEngine
{
    Task::~Task() {}

    void Task::onInit(void)
    {}

    void Task::onSuccess(void)
    {}

    void Task::onFail(void)
    {}

    void Task::onAbort(void)
    {}

    void Task::addChild(Task_sptr child)
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
