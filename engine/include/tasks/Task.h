#ifndef TASK_H_
#define TASK_H_

#include "Timer.h"

#include <assert.h>
#include <memory>

namespace pdEngine
{
    class Task;
    typedef std::shared_ptr<Task> Task_sptr;
    typedef std::weak_ptr<Task> Task_wptr;

    enum class TaskState
    {
        uninitialized,
        removed,
        running,
        paused,
        succeeded,
        failed,
        aborted
    };

    class Task
    {
        friend class TaskManager;

        TaskState   state       { TaskState::uninitialized };
        Task_sptr   childTask   { nullptr };

    public:
        virtual ~Task(void) =0;

        inline void succeed(void) { state = TaskState::succeeded; }
        inline void fail(void) { state = TaskState::failed; }

        inline void pause(void);
        inline void unPause(void);

        inline TaskState getState(void) const;
        inline bool isAlive(void) const;
        inline bool isDead(void) const;
        inline bool isRemoveD(void) const;
        inline bool isPaused(void) const;
        inline bool isUninitialized(void) const;

        void AttachChild(Task_sptr child);
        Task_sptr removeChild(void);
        Task_sptr peekChild(void);

    protected:
        virtual void onInit(void);
        virtual void onUpdate(TimeDelta) =0;
        virtual void onSuccess(void);
        virtual void onFail(void);
        virtual void onAbort(void);

    private:
    };
}

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

    bool Task::isUninitialized(void) const
    {
        return (state == TaskState::uninitialized);
    }
}

#endif
