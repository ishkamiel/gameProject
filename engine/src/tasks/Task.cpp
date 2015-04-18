#include "tasks/Task.h"

namespace pdEngine
{

Task::~Task()
{ }

void Task::onInit(void) noexcept
{ }

void Task::onSuccess(void) noexcept
{ }

void Task::onFail(void) noexcept
{ }

void Task::onAbort(void) noexcept
{ }

void Task::addChild(Task_sptr child) noexcept
{
    childTask = child;
}

Task_sptr Task::removeChild(void) noexcept
{
    auto retval = childTask;
    childTask = nullptr;

    return retval;
}

Task_sptr Task::peekChild(void) const noexcept
{
    return childTask;
}
}
