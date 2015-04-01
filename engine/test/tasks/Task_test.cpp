#include "tasks/Task_test.h"

void Task_test::SetUp()
{
    t.reset(new pdEngine::SimpleTask());
    t2.reset(new pdEngine::SimpleTask());
    t3.reset(new pdEngine::SimpleTask());
    t4.reset(new pdEngine::SimpleTask());

    tm = new pdEngine::TaskManager();
}

void Task_test::TearDown()
{
    delete tm;
}

TEST_F(Task_test, testConstructors) 
{
    ASSERT_TRUE(t->isUninitialized());
    ASSERT_EQ(t->getState(), pdEngine::TaskState::uninitialized);
}

TEST_F(Task_test, testInit) 
{
    tm->onInit(t);
    ASSERT_TRUE(t->isDead() || t->isUninitialized());
}

TEST_F(Task_test, testUpdate) 
{
    tm->onInit(t);
    ASSERT_TRUE(t->isDead() || t->isUninitialized());
    if (t->isUninitialized())
    {
        tm->setState(t, pdEngine::TaskState::running);
        tm->onUpdate(t, 1);
    }
}

TEST_F(Task_test, testStatesAndPause) 
{
    ASSERT_EQ(t->getState(), pdEngine::TaskState::uninitialized);
    ASSERT_FALSE(t->isAlive());
    ASSERT_FALSE(t->isDead());
    ASSERT_FALSE(t->isRemoved());
    ASSERT_FALSE(t->isPaused());
    ASSERT_TRUE(t->isUninitialized());

    tm->onInit(t);
    ASSERT_TRUE(t->isDead() || t->isUninitialized());
    if (t->isUninitialized())
    {
        tm->setState(t, pdEngine::TaskState::running);
        ASSERT_TRUE(t->isAlive());
        ASSERT_FALSE(t->isDead());
        ASSERT_FALSE(t->isRemoved());
        ASSERT_FALSE(t->isPaused());
        ASSERT_FALSE(t->isUninitialized());

        t->pause();
        ASSERT_TRUE(t->isAlive());
        ASSERT_FALSE(t->isDead());
        ASSERT_FALSE(t->isRemoved());
        ASSERT_TRUE(t->isPaused());
        ASSERT_FALSE(t->isUninitialized());

        t->unPause();
        ASSERT_TRUE(t->isAlive());
        ASSERT_FALSE(t->isDead());
        ASSERT_FALSE(t->isRemoved());
        ASSERT_FALSE(t->isPaused());
        ASSERT_FALSE(t->isUninitialized());

        t->unPause();
        t->unPause();
        ASSERT_FALSE(t->isPaused());

        t->pause();
        t->pause();
        t->pause();
        t->pause();
        t->pause();
        ASSERT_TRUE(t->isPaused());
        ASSERT_EQ(t->getState(), pdEngine::TaskState::paused);
        t->unPause();
        ASSERT_FALSE(t->isPaused());
        ASSERT_EQ(t->getState(), pdEngine::TaskState::running);
    }
}

TEST_F(Task_test, testFail) 
{
    tm->onInit(t);
    ASSERT_TRUE(t->isDead() || t->isUninitialized());
    if (t->isUninitialized())
    {
        t->fail();
        ASSERT_EQ(t->getState(), pdEngine::TaskState::failed);
        ASSERT_FALSE(t->isAlive());
        ASSERT_TRUE(t->isDead());
        ASSERT_FALSE(t->isRemoved());
        ASSERT_FALSE(t->isPaused());
        ASSERT_FALSE(t->isUninitialized());
    }
}

TEST_F(Task_test, testSucceed) 
{
    tm->onInit(t);
    ASSERT_TRUE(t->isDead() || t->isUninitialized());
    if (t->isUninitialized())
    {
        t->succeed();
        ASSERT_EQ(t->getState(), pdEngine::TaskState::succeeded);
        ASSERT_FALSE(t->isAlive());
        ASSERT_FALSE(t->isDead());
        ASSERT_FALSE(t->isRemoved());
        ASSERT_FALSE(t->isPaused());
        ASSERT_FALSE(t->isUninitialized());
    }
}

TEST_F(Task_test, TestChildren) 
{
    pdEngine::Task_sptr sptr_2 { t2 };
    pdEngine::Task_sptr sptr_3 { t3 };
    pdEngine::Task_sptr sptr_4 { t4 };

    t3->addChild(sptr_4);
    t2->addChild(sptr_3);
    t->addChild(sptr_2);

    ASSERT_TRUE(t->peekChild() == sptr_2);
    ASSERT_TRUE(t2->peekChild() == sptr_3);
    ASSERT_TRUE(t3->peekChild() == sptr_4);
    ASSERT_EQ(t3->peekChild(), sptr_4);
    ASSERT_TRUE(t3->removeChild() == sptr_4);
    ASSERT_FALSE(t3->removeChild());
    ASSERT_EQ(t2->removeChild(), sptr_3);
    ASSERT_EQ(t->removeChild(), sptr_2);
    ASSERT_FALSE(t->removeChild());
    ASSERT_FALSE(t->removeChild());
}
