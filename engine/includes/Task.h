#ifndef TASK_H_
#define TASK_H_

#include "General.h"

#include <assert.h>
#include <memory>

namespace pdEngine
{
    class ITask;
    typedef std::shared_ptr<ITask> TaskPtrS;
    typedef std::weak_ptr<ITask> TaskPtrW;

    class ITask
    {
        friend class TaskManager;

        public:
        enum class State
        {
            uninitialized,
            removed,
            running,
            paused,
            succeeded,
            failed,
            aborted
        };

        private:
        State state;
        TaskPtrS childTask;

        public:
        ITask(void);
        virtual ~ITask(void);

        protected:
        virtual void onInit(void);
        virtual void onUpdate(TimeDelta) =0;
        virtual void onSuccess(void);
        virtual void onFail(void);
        virtual void onAbort(void);

        public:
        inline void succeed(void) { state = State::succeeded; }
        inline void fail(void) { state = State::failed; }

        inline void pause(void);
        inline void unPause(void);

        inline State getState(void) const;
        inline bool isAlive(void) const;
        inline bool isDead(void) const;
        inline bool isRemoveD(void) const;
        inline bool isPaused(void) const;

        void AttachChild(TaskPtrS child);
        TaskPtrS removeChild(void);
        TaskPtrS peekChild(void);
    };
}

#include "Task_defs.h"

#endif
