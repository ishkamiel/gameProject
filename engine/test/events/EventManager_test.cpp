#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "events/EventTypeID.h"
#include "events/DefaultEvent.h"
#include "events/EventManager.h"
#include "events/ListenerHandle.h"
#include "tasks/Task.h"
#include "utils/Logger.h"

#include <cstring>

namespace pdEngine
{

class test_EventManager : public ::testing::Test
{
public:
    EventManager_sptr em;
    Task_sptr emTask;

protected:
    virtual void SetUp()
    {
        setGlobalLogLevel(LogLevel::trace);
        em = EventManager::get();
        emTask = std::static_pointer_cast<Task>(em);
        emTask->onInit();
    }
};


TEST_F(test_EventManager, Get)
{
    auto my_em = EventManager::get();
    ASSERT_FALSE(!my_em);
}

TEST_F(test_EventManager, CanCastToTask)
{
    auto my_em = EventManager::get();
    auto my_task = std::static_pointer_cast<Task>(em);
    ASSERT_FALSE(!my_task);
}

TEST_F(test_EventManager, AddListener)
{
    auto id = getEventID("TestEvent");

    ListenerHandle_sptr handle = em->addListener(
        id, [](Event_sptr event) {  return true; });
}

TEST_F(test_EventManager, WillUpdate)
{
    ASSERT_NO_THROW({ emTask->onUpdate(10); });
}

TEST_F(test_EventManager, SingleEventReachesListener)
{
    auto id = getEventID("TestEvent");

    auto wasCalled = false;

    ListenerHandle_sptr handle = em->addListener(
        id,
        [&](Event_sptr event) {
            wasCalled = true;
            return true;
        });

    em->queueEvent(std::make_shared<DefaultEvent>(id));
    emTask->onUpdate(10);

    ASSERT_TRUE(wasCalled);
}

}