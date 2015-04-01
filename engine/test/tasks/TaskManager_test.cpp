#include "tasks/TaskManager.h"

#include "tasks/MockTask.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::AtMost;
using ::testing::AtLeast;
using ::testing::InvokeWithoutArgs;

class TaskManager_test : public ::testing::Test
{
protected:
    std::shared_ptr<pdEngine::MockTask> t1;
    std::shared_ptr<pdEngine::MockTask> t2;
    std::shared_ptr<pdEngine::MockTask> t3;
    std::shared_ptr<pdEngine::MockTask> t4;

    std::shared_ptr<pdEngine::TaskManager> tm;

    TaskManager_test() {};
    virtual ~TaskManager_test() {};

    virtual void SetUp();
    virtual void TearDown();
};

void TaskManager_test::SetUp()
{
    t1.reset(new pdEngine::MockTask());
    t2.reset(new pdEngine::MockTask());
    t3.reset(new pdEngine::MockTask());
    t4.reset(new pdEngine::MockTask());
    EXPECT_CALL(*t1, onInit()).Times(AtMost(1));
    EXPECT_CALL(*t2, onInit()).Times(AtMost(1));
    EXPECT_CALL(*t3, onInit()).Times(AtMost(1));
    EXPECT_CALL(*t4, onInit()).Times(AtMost(1));
    tm.reset(new pdEngine::TaskManager());
}

void TaskManager_test::TearDown()
{
    t1.reset();
    t2.reset();
    t3.reset();
    t4.reset();
    tm.reset();
}

TEST_F(TaskManager_test, MakeSureTestingFacilitiesWorkAsExpected)
{
    EXPECT_EQ(t1->getState(), pdEngine::TaskState::uninitialized);
    EXPECT_CALL(*t1, onInit()).WillOnce(InvokeWithoutArgs(&*t1, &pdEngine::MockTask::fail));
    //t1->t_failInit();
    t1->onInit();
    EXPECT_EQ(t1->getState(), pdEngine::TaskState::failed);
}

TEST_F(TaskManager_test, testConstructors) 
{
    ASSERT_FALSE(!t1);
    ASSERT_FALSE(!tm);
}

TEST_F(TaskManager_test, addTasks) 
{
    ASSERT_EQ(tm->taskCount(), 0);
    tm->addTask(t1);
    ASSERT_EQ(tm->taskCount(), 1);
    tm->addTask(t2);
    tm->addTask(t3);
    tm->addTask(t4);
    ASSERT_EQ(tm->taskCount(), 4);
}

TEST_F(TaskManager_test, InitAll) 
{
    EXPECT_CALL(*t1, onInit()).Times(1);
    EXPECT_CALL(*t2, onInit()).Times(1);
    EXPECT_CALL(*t3, onInit()).Times(1);
    EXPECT_CALL(*t4, onInit()).Times(1);
    tm->addTask(t1);
    tm->addTask(t2);
    tm->addTask(t3);
    ASSERT_TRUE(tm->initAll());
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::ready);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::ready);
    ASSERT_EQ(t3->getState(), pdEngine::TaskState::ready);
    tm->addTask(t4);
    ASSERT_TRUE(tm->initAll());
    ASSERT_EQ(t4->getState(), pdEngine::TaskState::ready);
}

TEST_F(TaskManager_test, InitAllWithFails) 
{
    tm->addTask(t4);
    tm->addTask(t1);
    tm->addTask(t2);

    tm->addTask(t3);

    EXPECT_CALL(*t3, onInit()).WillOnce(InvokeWithoutArgs(&*t3, &pdEngine::MockTask::fail));
    ASSERT_FALSE(tm->initAll());
    ASSERT_EQ(t3->getState(), pdEngine::TaskState::failed);
}

TEST_F(TaskManager_test, SuccessfullTaskCycle) 
{
    EXPECT_CALL(*t1, onInit()).Times(1);
    EXPECT_CALL(*t1, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t1, onSuccess()).Times(1);
    EXPECT_CALL(*t1, onAbort()).Times(0);
    EXPECT_CALL(*t1, onFail()).Times(0);

    tm->addTask(t1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::uninitialized);
    tm->initAll();
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::ready);
    ASSERT_EQ(tm->taskCount(), 1);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    t1->succeed();
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::succeeded);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(tm->taskCount(), 0);
    tm->updateTasks(1);
    ASSERT_EQ(tm->taskCount(), 0);
}

TEST_F(TaskManager_test, FailingUpdates) 
{
    EXPECT_CALL(*t1, onInit()).Times(1);
    EXPECT_CALL(*t1, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t1, onSuccess()).Times(0);
    EXPECT_CALL(*t1, onAbort()).Times(0);
    EXPECT_CALL(*t1, onFail()).Times(1);
    tm->addTask(t1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);

    EXPECT_CALL(*t1, onUpdate(_)).WillOnce(InvokeWithoutArgs(&*t1, &pdEngine::Task::fail));
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::failed);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(tm->taskCount(), 0);
}

TEST_F(TaskManager_test, SucceedingUpdates)
{
    EXPECT_CALL(*t1, onInit()).Times(1);
    EXPECT_CALL(*t1, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t1, onSuccess()).Times(1);
    EXPECT_CALL(*t1, onAbort()).Times(0);
    EXPECT_CALL(*t1, onFail()).Times(0);

    tm->addTask(t1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);

    EXPECT_CALL(*t1, onUpdate(_)).WillOnce(InvokeWithoutArgs(&*t1, &pdEngine::Task::succeed));
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::succeeded);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(tm->taskCount(), 0);
}

TEST_F(TaskManager_test, AbortAllWithJustOne)
{
    EXPECT_CALL(*t1, onInit()).Times(1);
    EXPECT_CALL(*t1, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t1, onSuccess()).Times(0);
    EXPECT_CALL(*t1, onAbort()).Times(1);
    EXPECT_CALL(*t1, onFail()).Times(0);

    tm->addTask(t1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);

    tm->abortAllNow();

    ASSERT_EQ(t1->getState(), pdEngine::TaskState::aborted);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(tm->taskCount(), 0);
}

TEST_F(TaskManager_test, AbortAllWithMoreTasks)
{
    EXPECT_CALL(*t1, onInit()).Times(1);
    EXPECT_CALL(*t1, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t1, onSuccess()).Times(0);
    EXPECT_CALL(*t1, onAbort()).Times(1);
    EXPECT_CALL(*t1, onFail()).Times(0);

    EXPECT_CALL(*t2, onInit()).Times(1);
    EXPECT_CALL(*t2, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t2, onSuccess()).Times(0);
    EXPECT_CALL(*t2, onAbort()).Times(1);
    EXPECT_CALL(*t2, onFail()).Times(0);

    EXPECT_CALL(*t3, onInit()).Times(1);
    EXPECT_CALL(*t3, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t3, onSuccess()).Times(0);
    EXPECT_CALL(*t3, onAbort()).Times(1);
    EXPECT_CALL(*t3, onFail()).Times(0);

    EXPECT_CALL(*t4, onInit()).Times(1);
    EXPECT_CALL(*t4, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t4, onSuccess()).Times(0);
    EXPECT_CALL(*t4, onAbort()).Times(1);
    EXPECT_CALL(*t4, onFail()).Times(0);
    tm->addTask(t1);
    tm->addTask(t2);
    tm->addTask(t3);
    tm->addTask(t4);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->abortAllNow();
    ASSERT_EQ(tm->taskCount(), 4);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::aborted);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::aborted);
    ASSERT_EQ(t3->getState(), pdEngine::TaskState::aborted);
    ASSERT_EQ(t4->getState(), pdEngine::TaskState::aborted);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(tm->taskCount(), 0);
}

TEST_F(TaskManager_test, AlotWithPause)
{
    auto tasks = 100;
    auto iterations  = 100000;

    EXPECT_CALL(*t1, onInit()).Times(1);
    EXPECT_CALL(*t1, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t1, onSuccess()).Times(1);
    EXPECT_CALL(*t1, onAbort()).Times(0);
    EXPECT_CALL(*t1, onFail()).Times(0);

    EXPECT_CALL(*t2, onInit()).Times(1);
    EXPECT_CALL(*t2, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t2, onSuccess()).Times(1);
    EXPECT_CALL(*t2, onAbort()).Times(0);
    EXPECT_CALL(*t2, onFail()).Times(0);

    EXPECT_CALL(*t3, onInit()).Times(1);
    EXPECT_CALL(*t3, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t3, onSuccess()).Times(0);
    EXPECT_CALL(*t3, onAbort()).Times(0);
    EXPECT_CALL(*t3, onFail()).Times(1);

    EXPECT_CALL(*t4, onInit()).Times(1);
    EXPECT_CALL(*t4, onUpdate(_)).Times(AtLeast(1));
    EXPECT_CALL(*t4, onSuccess()).Times(1);
    EXPECT_CALL(*t4, onAbort()).Times(0);
    EXPECT_CALL(*t4, onFail()).Times(0);

    for (auto i = 0; i < tasks; ++i)
    {
        auto t = std::make_shared<pdEngine::MockTask>();
        EXPECT_CALL(*t, onInit()).Times(1);
        EXPECT_CALL(*t, onUpdate(_)).Times(AtLeast(1));
        EXPECT_CALL(*t, onSuccess()).Times(0);
        EXPECT_CALL(*t, onAbort()).Times(0);
        EXPECT_CALL(*t, onFail()).Times(0);
    }
    tm->addTask(t1);
    tm->addTask(t2);
    tm->addTask(t3);
    tm->addTask(t4);
    for (auto i = 0; i < tasks; ++i)
    {
        auto t = std::make_shared<pdEngine::MockTask>();
        EXPECT_CALL(*t, onInit()).Times(1);
        EXPECT_CALL(*t, onUpdate(_)).Times(AtLeast(1));
        EXPECT_CALL(*t, onSuccess()).Times(0);
        EXPECT_CALL(*t, onAbort()).Times(0);
        EXPECT_CALL(*t, onFail()).Times(0);
    }

    tm->updateTasks(1);
    tm->updateTasks(1);
    t4->pause();
    for (auto i = 0; i < 1000000; i++)
    {
        if (i == 500000)
            t4->unPause();
        tm->updateTasks(1);
    }
    ASSERT_EQ(t1->updateCount, 1000000);
    ASSERT_EQ(t2->updateCount, 1000000);
    ASSERT_EQ(t3->updateCount, 1000000);
    ASSERT_EQ(t4->updateCount, 500000);
}

// TEST_F(TaskManager_test, AnyDead)
// {
//     t1->failOnInit = true;
//     tm->addTask(t1);
//     tm->addTask(t2);
//     tm->addTask(t3);
//     tm->addTask(t4);
//     tm->initAll();
//     ASSERT_TRUE(tm->areAnyDead());
// }


// bool initAll();
// void abortAllNow();
// void addTask(Task_sptr);
// void updateTasks(TimeDelta);
// void pauseTasks();
// void unPauseTasks();
// bool areAnyDead();

