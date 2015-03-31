#include "tasks/MockTask.h"

#include "tasks/TaskManager.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class TaskManager_test : public ::testing::Test
{
protected:
    std::shared_ptr<pdEngine::Task> t1;
    std::shared_ptr<pdEngine::Task> t2;
    std::shared_ptr<pdEngine::Task> t3;
    std::shared_ptr<pdEngine::Task> t4;
    std::shared_ptr<pdEngine::Task> t_failInit;
    std::shared_ptr<pdEngine::Task> t_failUpdate;

    std::shared_ptr<pdEngine::TaskManager> tm;

    TaskManager_test() {};
    virtual ~TaskManager_test() {};

    virtual void SetUp();
    virtual void TearDown();

    void failNextUpdate(std::shared_ptr<pdEngine::Task> ptr);
};

void TaskManager_test::failNextUpdate(std::shared_ptr<pdEngine::Task> ptr)
{
    std::shared_ptr<pdEngine::MockTask> mt = std::static_pointer_cast<pdEngine::MockTask>(ptr);
    mt->failOnUpdate = true;
}

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

TEST_F(TaskManager_test, testInitAll) 
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

TEST_F(TaskManager_test, testInitAllWithFails) 
{
    tm->addTask(t4);
    tm->addTask(t1);
    tm->addTask(t2);
    tm->addTask(t_failInit);
    tm->addTask(t3);
    ASSERT_FALSE(tm->initAll());
    ASSERT_EQ(t_failInit->getState(), pdEngine::TaskState::failed);
}

TEST_F(TaskManager_test, testSuccessfullTaskCycle) 
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

TEST_F(TaskManager_test, testFailingUpdates) 
{
    tm->addTask(t1);
    tm->updateTasks(1);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    tm->updateTasks(1);
    failNextUpdate(t1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::running);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::failed);
    tm->updateTasks(1);
    ASSERT_EQ(t1->getState(), pdEngine::TaskState::removed);
}


// bool initAll();
// void abortAllNow();
// void addTask(Task_sptr);
// void updateTasks(TimeDelta);
// void pauseTasks();
// void unPauseTasks();
// bool areAnyDead();

