#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "utils/Timer.h"

#include <chrono>
#include <thread>

namespace pdEngineTest
{

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
  auto first = pdEngine::Timer::now();
  auto second = pdEngine::Timer::now();
  EXPECT_TRUE(first < second);
}

TEST_F(Timer_test, TimerTotalTimes)
{
  pdEngine::Timer t {1000};
  EXPECT_EQ(t.getStepDeltaMs(), 1);

  auto micro = t.totalMicro();
  auto milli = t.totalMilli();
  auto seconds = t.totalSeconds();
  EXPECT_TRUE(micro/1000 <= milli);
  EXPECT_TRUE(milli/1000 <= seconds);
}

TEST_F(Timer_test, OneSecondStep)
{
  pdEngine::Timer t {1};
  EXPECT_TRUE(t.step());
  EXPECT_FALSE(t.step());
}

TEST_F(Timer_test, OneMsStep)
{
  pdEngine::Timer t {1000};
  EXPECT_TRUE(t.step());
  EXPECT_FALSE(t.step());
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  EXPECT_TRUE(t.step());
}

}
  