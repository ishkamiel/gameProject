#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "events/EventTypeID.h"
#include "events/DefaultEvent.h"
#include "events/EventManager.h"
#include "events/ListenerHandle.h"
#include "tasks/Task.h"
#include "utils/Logger.h"

#include <cstring>
#include <list>

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
        setGlobalLogLevel(LogLevel::fatal);
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

TEST_F(test_EventManager, SeveralListenersSeveralUpdates)
{
    auto id = getEventID("TestEvent");

    auto callsToFirst = 0;
    auto callsToSecond = 0;

    ListenerHandle_sptr first = em->addListener(
        id,
        [&](Event_sptr event) {
            ++callsToFirst;
            return true;
        });

    ListenerHandle_sptr second = em->addListener(
        id,
        [&](Event_sptr event) {
            ++callsToSecond;
            return true;
        });

    emTask->onUpdate(10);

    ASSERT_EQ(callsToFirst, 0);
    ASSERT_EQ(callsToSecond, 0);
    em->queueEvent(std::make_shared<DefaultEvent>(id));
    emTask->onUpdate(10);
    ASSERT_EQ(callsToFirst, 1);
    ASSERT_EQ(callsToSecond, 1);

    emTask->onUpdate(10);
    emTask->onUpdate(10);
    emTask->onUpdate(10);
    ASSERT_EQ(callsToFirst, 1);
    ASSERT_EQ(callsToSecond, 1);
    first.reset();
    em->queueEvent(std::make_shared<DefaultEvent>(id));
    em->onUpdate(10);
    ASSERT_EQ(callsToFirst, 1);
    ASSERT_EQ(callsToSecond, 2);
}

TEST_F(test_EventManager, EventProcessingResettingEvent)
{
    auto id = getEventID("TestEvent");

    auto callsToFirst = 0;
    auto callsToSecond = 0;

    ListenerHandle_sptr second;

    ListenerHandle_sptr first = em->addListener(
        id,
        [&](Event_sptr event) {
            ++callsToFirst;
            second.reset();
            return true;
        });

    second = em->addListener(
        id,
        [&](Event_sptr event) {
            ++callsToSecond;
            return true;
        });

    em->queueEvent(std::make_shared<DefaultEvent>(id));
    emTask->onUpdate(10);
    ASSERT_EQ(callsToFirst, 1);
    ASSERT_EQ(callsToSecond, 0);
}

TEST_F(test_EventManager, ListenerCanCancelCallChain)
{
    auto id = getEventID("TestEvent");

    auto first = em->addListener(
        id,
        [&](Event_sptr event) {
            return false;
        });


    auto wasCalled = false;
    auto second = em->addListener(
        id,
        [&](Event_sptr event) {
            wasCalled = true;
            return true;
        });

    em->queueEvent(std::make_shared<DefaultEvent>(id));
    emTask->onUpdate(10);
    ASSERT_FALSE(wasCalled);
}

TEST_F(test_EventManager, SeveralListenersAndEventTypes)
{
    auto callCount = 0;
    auto expected = 0;
    auto typesToCreate = 100;
    auto listenersToCreate = 10;

    std::list<EventTypeID> ids;
    std::list<ListenerHandle_sptr> handles;

    for (auto i = 0; i < typesToCreate; ++i) {
        ids.push_back(i+1248);
    }

    for (auto id : ids) {
        for (auto i = 0; i < listenersToCreate; ++i) {
            handles.push_back(em->addListener(
                id,
                [&](Event_sptr event) {
                    ++callCount;
                    return true;
                }));
        }
    }

    em->queueEvent(std::make_shared<DefaultEvent>(ids.front()));
    emTask->onUpdate(10);

    expected += listenersToCreate;
    ASSERT_EQ(callCount, expected);

    em->queueEvent(std::make_shared<DefaultEvent>(ids.front()));
    em->queueEvent(std::make_shared<DefaultEvent>(ids.front()));
    em->queueEvent(std::make_shared<DefaultEvent>(ids.front()));
    emTask->onUpdate(10);

    expected += 3*listenersToCreate;
    ASSERT_EQ(callCount, expected);

    for (auto id : ids) {
        em->queueEvent(std::make_shared<DefaultEvent>(id));
    }
    emTask->onUpdate(10);

    expected += listenersToCreate*typesToCreate;
    ASSERT_EQ(callCount, expected);

    handles.clear();
    for (auto id : ids) {
        em->queueEvent(std::make_shared<DefaultEvent>(id));
    }
    emTask->onUpdate(10);

    ASSERT_EQ(callCount, expected);
}

}