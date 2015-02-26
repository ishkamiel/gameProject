#ifndef TASK_DEFS_H_
#define TASK_DEFS_H_

#include "Task.h"

namespace pdEngine
{
    void Task::pause(void) 
    {
        assert(isAlive());
        state = State::paused;
    };

    void Task::unPause(void)
    {
        assert(isAlive());
        state = State::running;
    };

    Task::State Task::getState(void) const 
    { 
        return (state); 
    }

    bool Task::isAlive(void) const 
    { 
        return (state == State::running || state == State::paused); 
    }

    bool Task::isDead(void) const 
    { 
        return (state == State::failed || state == State::aborted); 
    }

    bool Task::isRemoveD(void) const { 
        return (state == State::removed); 
    }

    bool Task::isPaused(void) const 
    { 
        return (state == State::paused); 
    }
}

#endif
