#ifndef TASK_DEFS_H_
#define TASK_DEFS_H_

#include "Task.h"

namespace pdEngine
{
    void Task::pause(void) 
    {
        assert(isAlive());
        state = TaskState::paused;
    }

    void Task::unPause(void)
    {
        assert(isAlive());
        state = TaskState::running;
    }

    TaskState Task::getState(void) const 
    { 
        return (state); 
    }

    bool Task::isAlive(void) const 
    { 
        return (state == TaskState::running || state == TaskState::paused); 
    }

    bool Task::isDead(void) const 
    { 
        return (state == TaskState::failed || state == TaskState::aborted); 
    }

    bool Task::isRemoveD(void) const { 
        return (state == TaskState::removed); 
    }

    bool Task::isPaused(void) const 
    { 
        return (state == TaskState::paused); 
    }
}

#endif
