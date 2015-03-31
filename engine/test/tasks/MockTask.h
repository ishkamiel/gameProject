#ifndef MOCKTASK_H_
#define MOCKTASK_H_

#include "tasks/Task.h"

namespace pdEngine
{
    class MockTask : public Task
    {
    public:
        int updateCount { 0 };
        bool failOnInit { false };
        bool failOnUpdate { false };

        MockTask(void) {};
        virtual ~MockTask(void) {};

        virtual void onInit() { if (failOnInit) fail(); }
        virtual void onUpdate(TimeDelta) { ++updateCount; if (failOnUpdate) fail(); };
    };
}

#endif /* MOCKTASK_H_ */
