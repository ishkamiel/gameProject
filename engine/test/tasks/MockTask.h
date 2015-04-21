#pragma once

#include "tasks/Task.h"

/*
 * #include "gmock/gmock.h"
 * Google Mock didn't lick noexcept functions, so here we are...
 */

namespace pdEngine
{

class MockTask : public Task
{
public:
    bool m_failOnUpdate = false;
    bool m_failOnInit = false;

    int m_callsToInit = 0;
    int m_callsToUpdate = 0;

public:
    MockTask() {}
    virtual ~MockTask() {}

    std::string v_getTaskName(void) const noexcept override { return "MockTask"; }

    virtual inline void onUpdate(int t) noexcept override
    {
        (void)t;
        ++m_callsToUpdate;
        if (m_failOnUpdate) fail();
    }
    virtual inline void onInit() noexcept override
    {
        ++m_callsToInit;
        if (m_failOnInit) fail();
        Task::onInit();
    }
};

}

