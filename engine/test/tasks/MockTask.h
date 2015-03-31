#ifndef MOCKTASK_H_
#define MOCKTASK_H_

#include "tasks/Task.h"

namespace pdEngine
{
    class MockTask : public Task
    {
    public:
        int updateCount { 0 };
        int abortCount { 0 };
        int failCount { 0 };
        int succeedCount { 0 };
        int initCount { 0 };

        bool failOnInit { false };
        bool failOnUpdate { false };
        bool succeedOnUpdate { false };

        MockTask(void) {};
        virtual ~MockTask(void) {};

        virtual void onInit() 
        { 
            if (failOnInit) fail(); 
        }
        virtual void onUpdate(TimeDelta) 
        { 
            ++updateCount; 

            if (failOnUpdate) 
                fail(); 
            else if (succeedOnUpdate) 
                succeed(); 
        };
    };
}

#endif /* MOCKTASK_H_ */
