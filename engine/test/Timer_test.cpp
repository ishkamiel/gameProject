#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Timer.h"

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

TEST_F(Timer_test, notImplemented) {
    EXPECT_TRUE(false);
}
