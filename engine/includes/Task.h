#ifndef TASK_H_
#define TASK_H_

#include "General.h"

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

#include "Task_defs.h"

#endif
