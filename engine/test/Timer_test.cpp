#include "gtest/gtest.h"
#include "gmock/gmock.h"

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

TEST_F(Timer_test, ByDefaultBazTrueIsTrue) {
    EXPECT_EQ(true, true);
}

TEST_F(Timer_test, ByDefaultBazFalseIsFalse) {
    EXPECT_EQ(true, true);
}
