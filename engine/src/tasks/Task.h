#pragma once

#include "Timer.h"

#include <assert.h>
#include <memory>

namespace pdEngine
{
class Task;
using Task_sptr = std::shared_ptr<Task>;
using Task_wptr = std::weak_ptr<Task>;

enum class TaskState
{
    uninitialized,
    ready,
    running,
    paused,
    succeeded,
    removed,
    failed,
    aborted
};

class Task
{
    friend class TaskManager;

public:
    virtual ~Task(void) =0;

    inline void succeed(void) noexcept { state = TaskState::succeeded; }
    inline void fail(void) noexcept { state = TaskState::failed; }

    inline void pause(void) noexcept;
    inline void unPause(void) noexcept;

    inline TaskState getState(void) const noexcept;
    inline bool isAlive(void) const noexcept;
    inline bool isDead(void) const noexcept;
    inline bool isRemoved(void) const noexcept;
    inline bool isPaused(void) const noexcept;
    inline bool isUninitialized(void) const noexcept;

    void addChild(Task_sptr child) noexcept;
    Task_sptr removeChild(void) noexcept;
    Task_sptr peekChild(void) const noexcept;

protected:
    virtual void onInit(void) noexcept;
    virtual void onUpdate(int deltaMs) noexcept =0;
    virtual void onSuccess(void) noexcept;
    virtual void onFail(void) noexcept;
    virtual void onAbort(void) noexcept;

    inline void readyToRun(void) noexcept { state = TaskState::ready; }

private:
    TaskState   state       { TaskState::uninitialized };
    Task_sptr   childTask   { nullptr };
};

/*
 * Implementations
 */

void Task::pause(void) noexcept
{
    assert(isAlive());
    state = TaskState::paused;
}

void Task::unPause(void) noexcept
{
    assert(isAlive());
    state = TaskState::running;
}

TaskState Task::getState(void) const noexcept
{
    return (state);
}

bool Task::isAlive(void) const noexcept
{
    return (state == TaskState::running ||
            state == TaskState::ready ||
            state == TaskState::paused);
}

bool Task::isDead(void) const noexcept
{
    return (state == TaskState::failed || state == TaskState::aborted);
}

bool Task::isRemoved(void) const  noexcept
{
    return (state == TaskState::removed);
}

bool Task::isPaused(void) const noexcept
{
    return (state == TaskState::paused);
}

bool Task::isUninitialized(void) const noexcept
{
    return (state == TaskState::uninitialized);
}

}
