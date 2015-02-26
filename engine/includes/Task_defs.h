#ifndef TASK_DEFS_H_
#define TASK_DEFS_H_

#include "Task.h"

namespace pdEngine
{
    void ITask::pause(void) 
    {
        assert(isAlive());
        state = State::paused;
    };

    void ITask::unPause(void)
    {
        assert(isAlive());
        state = State::running;
    };

    ITask::State ITask::getState(void) const 
    { 
        return (state); 
    }

    bool ITask::isAlive(void) const 
    { 
        return (state == State::running || state == State::paused); 
    }

    bool ITask::isDead(void) const 
    { 
        return (state == State::failed || state == State::aborted); 
    }

    bool ITask::isRemoveD(void) const { 
        return (state == State::removed); 
    }

    bool ITask::isPaused(void) const 
    { 
        return (state == State::paused); 
    }
}

#endif
