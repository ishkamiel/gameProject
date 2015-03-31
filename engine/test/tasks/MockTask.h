#ifndef MOCKTASK_H_
#define MOCKTASK_H_

#include "tasks/Task.h"

namespace pdEngine
{
    class MockTask : public Task
    {
    public:
        int updateCount { 0 };

        MockTask(void) {};
        virtual ~MockTask(void) {};

        virtual void onUpdate(TimeDelta) { ++updateCount; };
    };
}

#endif /* MOCKTASK_H_ */
