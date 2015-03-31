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


        // bool initAll();
        // void abortAllNow();
        // void addTask(Task_sptr);
        // void updateTasks(TimeDelta);
        // void pauseTasks();
        // void unPauseTasks();
        // bool areAnyDead();

