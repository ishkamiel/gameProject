#include "tasks/MockTask.h"

#include "tasks/TaskManager.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class TaskManager_test : public ::testing::Test
{
protected:
    std::shared_ptr<pdEngine::MockTask> t1;
    std::shared_ptr<pdEngine::MockTask> t2;
    std::shared_ptr<pdEngine::MockTask> t3;
    std::shared_ptr<pdEngine::MockTask> t4;
    std::shared_ptr<pdEngine::MockTask> t_failInit;
    std::shared_ptr<pdEngine::MockTask> t_failUpdate;

    std::shared_ptr<pdEngine::TaskManager> tm;

    TaskManager_test() {};
    virtual ~TaskManager_test() {};

    virtual void SetUp();
    virtual void TearDown();
};

// void TaskManager_test::failNextUpdate(std::shared_ptr<pdEngine::Task> ptr)
// {
//     std::shared_ptr<pdEngine::MockTask> mt = std::static_pointer_cast<pdEngine::MockTask>(ptr);
//     mt->failOnUpdate = true;
// }

void TaskManager_test::SetUp()
{
    t1.reset(new pdEngine::MockTask());
    t2.reset(new pdEngine::MockTask());
    t3.reset(new pdEngine::MockTask());
    t4.reset(new pdEngine::MockTask());

    auto initFail = new pdEngine::MockTask();
    initFail->failOnInit = true;
    auto updateFail = new pdEngine::MockTask();
    updateFail->failOnUpdate = true;

    t_failInit.reset(initFail);
    t_failUpdate.reset(updateFail);

    tm.reset(new pdEngine::TaskManager());
}

void TaskManager_test::TearDown()
{}

TEST_F(TaskManager_test, testConstructors) 
{
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
    tm->addTask(t_failInit);
    tm->addTask(t3);
    ASSERT_FALSE(tm->initAll());
    ASSERT_EQ(t_failInit->getState(), pdEngine::TaskState::failed);
}

TEST_F(TaskManager_test, SuccessfullTaskCycle) 
{
    tm->addTask(t1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::uninitialized);
    tm->initAll();
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::ready);
    ASSERT_EQ(tm->taskCount(), 1);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    tm->addTask(t2);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::uninitialized);
    ASSERT_EQ(tm->taskCount(), 2);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::ready);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::running);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::running);
    ASSERT_EQ(tm->taskCount(), 2);
    t1->succeed();
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::succeeded);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::running);
    t1->succeed();
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::running);
    ASSERT_EQ(tm->taskCount(), 1);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::running);
    t2->succeed();
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::succeeded);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(tm->taskCount(), 0);
}

TEST_F(TaskManager_test, FailingUpdates) 
{
    tm->addTask(t1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);

    int uc = t1->updateCount;
    t1->failOnUpdate = true;

    // Run an update during which a fail occurs
    tm->updateTasks(1);
    ASSERT_EQ(t1->updateCount, uc+1);
    ASSERT_EQ(t1->failCount, 0);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::failed);

    // Process onFail and remove
    tm->updateTasks(1);
    ASSERT_EQ(t1->failCount, 1);
    ASSERT_EQ(t1->updateCount, uc+1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
    ASSERT_EQ(tm->taskCount(), 0);
}

TEST_F(TaskManager_test, SucceedingUpdates)
{
    tm->addTask(t1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);

    t1->succeedOnUpdate = true;

    // Next update will cause success
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::succeeded);
    ASSERT_EQ(t1->succeedCount, 0);

    // Next update will run onSuccess and remove
    tm->updateTasks(1);
    ASSERT_EQ(t1->succeedCount, 1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
}

TEST_F(TaskManager_test, Abort)
{
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
    ASSERT_EQ(t1->abortCount, 1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::aborted);
    ASSERT_EQ(t2->abortCount, 1);
    ASSERT_EQ(t2->getState(), pdEngine::TaskState::aborted);
    ASSERT_EQ(t3->abortCount, 1);
    ASSERT_EQ(t3->getState(), pdEngine::TaskState::aborted);
    ASSERT_EQ(t4->abortCount, 1);
    ASSERT_EQ(t4->getState(), pdEngine::TaskState::aborted);
}

TEST_F(TaskManager_test, AlotWithPause)
{
    tm->addTask(t1);
    tm->addTask(t2);
    tm->addTask(t3);
    tm->addTask(t4);
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

TEST_F(TaskManager_test, AnyDead)
{
    t1->failOnInit = true;
    tm->addTask(t1);
    tm->addTask(t2);
    tm->addTask(t3);
    tm->addTask(t4);
    tm->initAll();
    ASSERT_TRUE(tm->areAnyDead());
}


// bool initAll();
// void abortAllNow();
// void addTask(Task_sptr);
// void updateTasks(TimeDelta);
// void pauseTasks();
// void unPauseTasks();
// bool areAnyDead();

