#include "tasks/MockTask.h"

#include <gtest/gtest.h>
#include <memory>

namespace  pdEngine
{

class TaskManager
{
public:

  void onInit(Task_sptr t) { t->onInit(); }
  void onUpdate(Task_sptr t, int td) { t->onUpdate(td); }
  void onSuccess(Task_sptr t) { t->onSuccess(); }
  void onFail(Task_sptr t) { t->onFail(); }
  void onAbort(Task_sptr t) { t->onAbort(); }
  void setState(Task_sptr t, pdEngine::TaskState state) { t->state = state; }
};

class Task_test : public ::testing::Test
{
protected:
  std::unique_ptr<pdEngine::TaskManager> fake_tm;

  std::shared_ptr<Task> task;
  MockTask* mock;

  Task_test() {};

  virtual ~Task_test() {};

  virtual void SetUp() {
    fake_tm.reset(new pdEngine::TaskManager);
    mock = new MockTask();
    task = std::shared_ptr<Task>(mock);
  }

  virtual void TearDown() {
    fake_tm.reset();
    task.reset(); // destructs mt too...
  }
};

TEST_F(Task_test, FreshTasksAreUninitialized)
{
  ASSERT_TRUE(task->isUninitialized());
  ASSERT_EQ(task->getState(), pdEngine::TaskState::uninitialized);
}

TEST_F(Task_test, onInitSetsStateToReady)
{
  fake_tm->onInit(task);
  ASSERT_EQ(task->getState(), pdEngine::TaskState::ready);
}

TEST_F(Task_test, onInitFailingStays)
{
  mock->m_failOnInit = true;
  fake_tm->onInit(task);
  ASSERT_EQ(task->getState(), pdEngine::TaskState::failed);
}

TEST_F(Task_test, isDead)
{
  ASSERT_FALSE(task->isDead());
  fake_tm->onInit(task);
  ASSERT_FALSE(task->isDead());
  task->fail();
  ASSERT_TRUE(task->isDead());
}

TEST_F(Task_test, isAlive)
{
  ASSERT_FALSE(task->isAlive());
  fake_tm->onInit(task);
  ASSERT_TRUE(task->isAlive());
  task->fail();
  ASSERT_FALSE(task->isAlive());
}

TEST_F(Task_test, isUninitialized)
{
  ASSERT_TRUE(task->isUninitialized());
  fake_tm->onInit(task);
  ASSERT_FALSE(task->isUninitialized());
  task->fail();
  ASSERT_FALSE(task->isUninitialized());
}

TEST_F(Task_test, testStatesAndPause)
{
  ASSERT_EQ(task->getState(), pdEngine::TaskState::uninitialized);
  ASSERT_FALSE(task->isAlive());
  ASSERT_FALSE(task->isDead());
  ASSERT_FALSE(task->isRemoved());
  ASSERT_FALSE(task->isPaused());
  ASSERT_TRUE(task->isUninitialized());

  fake_tm->onInit(task);
  ASSERT_EQ(task->getState(), TaskState::ready);

    fake_tm->setState(task, pdEngine::TaskState::running);
    ASSERT_TRUE(task->isAlive());
    ASSERT_FALSE(task->isDead());
    ASSERT_FALSE(task->isRemoved());
    ASSERT_FALSE(task->isPaused());
    ASSERT_FALSE(task->isUninitialized());

    task->pause();
    ASSERT_TRUE(task->isAlive());
    ASSERT_FALSE(task->isDead());
    ASSERT_FALSE(task->isRemoved());
    ASSERT_TRUE(task->isPaused());
    ASSERT_FALSE(task->isUninitialized());

    task->unPause();
    ASSERT_TRUE(task->isAlive());
    ASSERT_FALSE(task->isDead());
    ASSERT_FALSE(task->isRemoved());
    ASSERT_FALSE(task->isPaused());
    ASSERT_FALSE(task->isUninitialized());

    task->unPause();
    task->unPause();
    ASSERT_FALSE(task->isPaused());

    task->pause();
    task->pause();
    task->pause();
    task->pause();
    task->pause();
    ASSERT_TRUE(task->isPaused());
    ASSERT_EQ(task->getState(), pdEngine::TaskState::paused);
    task->unPause();
    ASSERT_FALSE(task->isPaused());
    ASSERT_EQ(task->getState(), pdEngine::TaskState::running);
    task->unPause();
    task->unPause();
    ASSERT_FALSE(task->isPaused());
    ASSERT_EQ(task->getState(), pdEngine::TaskState::running);
}

TEST_F(Task_test, testFail)
{
  task->fail();
  ASSERT_EQ(task->getState(), pdEngine::TaskState::failed);
  ASSERT_FALSE(task->isAlive());
  ASSERT_TRUE(task->isDead());
  ASSERT_FALSE(task->isRemoved());
  ASSERT_FALSE(task->isPaused());
  ASSERT_FALSE(task->isUninitialized());
}

TEST_F(Task_test, testSucceed)
{
  fake_tm->onInit(task);
  task->succeed();
  ASSERT_EQ(task->getState(), pdEngine::TaskState::succeeded);
  ASSERT_FALSE(task->isAlive());
  ASSERT_FALSE(task->isDead());
  ASSERT_FALSE(task->isRemoved());
  ASSERT_FALSE(task->isPaused());
  ASSERT_FALSE(task->isUninitialized());
}

TEST_F(Task_test, TestChildren)
{
  std::shared_ptr<Task> t2 = std::make_shared<MockTask>();
  std::shared_ptr<Task> t3 = std::make_shared<MockTask>();
  std::shared_ptr<Task> t4 = std::make_shared<MockTask>();

  t3->addChild(t4);
  t2->addChild(t3);
  task->addChild(t2);

  ASSERT_TRUE(task->peekChild() == t2);
  ASSERT_TRUE(t2->peekChild() == t3);
  ASSERT_TRUE(t3->peekChild() == t4);
  ASSERT_EQ(t3->peekChild(), t4);
  ASSERT_TRUE(t3->removeChild() == t4);
  ASSERT_TRUE(!t3->removeChild());
  ASSERT_EQ(t2->removeChild(), t3);
  ASSERT_EQ(task->removeChild(), t2);
  //ASSERT_FALSE(t->removeChild());
  //ASSERT_FALSE(t->removeChild());
}

}
  