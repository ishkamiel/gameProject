#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Timer.h"

#include <chrono>
#include <thread>

class Timer_test : public ::testing::Test 
{

protected:
    Timer_test();
    virtual ~Timer_test();

    virtual void SetUp();
    virtual void TearDown();
};

Timer_test::Timer_test()
{}

Timer_test::~Timer_test()
{}

void Timer_test::SetUp()
{}

void Timer_test::TearDown()
{}

TEST_F(Timer_test, now)
{
    auto first = pdEngine::now();
    auto second = pdEngine::now();
    EXPECT_TRUE(first < second);
}

TEST_F(Timer_test, TimerTotalTimes) 
{
    pdEngine::Timer t {1000};
    pdEngine::TimeDelta delta = t.stepAndSleep();
    EXPECT_TRUE(delta > 0);

    pdEngine::TimeMicro micro = t.totalMicro();
    pdEngine::TimeMilli milli = t.totalMilli();
    EXPECT_EQ(micro/1000, milli);
    EXPECT_EQ(milli/1000, t.totalSeconds());
}

TEST_F(Timer_test, deltaTimes)
{
    pdEngine::Timer t {1000};
    auto delta = t.stepAndSleep();
    auto micro = t.deltaMicro();
    auto milli = t.deltaMilli();
    EXPECT_EQ(micro/1000, milli);
    EXPECT_EQ(delta/1000, micro);
}

TEST_F(Timer_test, Lag)
{
    pdEngine::Timer t {1000};

    t.stepAndSleep();

    auto before = pdEngine::now();
    auto d1 = t.stepAndSleep();
    auto after = pdEngine::now();

    std::this_thread::sleep_for((after-before) * 2);

    auto d2 = t.stepAndSleep();
    auto d3 = t.stepAndSleep();

    EXPECT_TRUE(d2 > d3);
    EXPECT_TRUE(d2 > d1);
}
