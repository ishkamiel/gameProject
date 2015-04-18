#ifndef MOCKTASK_H_
#define MOCKTASK_H_

#include "tasks/Task.h"

#include "gmock/gmock.h"

/*
namespace pdEngine
{
    class SimpleTask : public Task
    {
    public:
        SimpleTask() {};
        virtual ~SimpleTask() {};
        virtual void onUpdate(TimeDelta t) noexcept override
        {
            (void)t; 
            if (m_FailU) fail(); 
        }
        virtual void onInit() noexcept override
        { 
            if (m_FailI) fail();
        }
        
        void t_failNextUpdate() { m_FailU = true; };
        void t_failInit() { m_FailI = true; };
        bool m_FailU { false };
        bool m_FailI { false };
    };

    class MockTask : public Task
    {
    public:
        //MOCK_METHOD0(onInit, void(void));
        //MOCK_METHOD0(onAbort, void(void));
        //MOCK_METHOD0(onFail, void(void));
        //MOCK_METHOD0(onSuccess, void(void));
        //MOCK_METHOD1(onUpdate, void(TimeDelta));
    };
}
 */

#endif /* MOCKTASK_H_ */
