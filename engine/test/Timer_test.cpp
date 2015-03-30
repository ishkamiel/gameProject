#include "Timer_test.h"

int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( Timer_test::suite() );
    runner.run();
    return (0);
}

void Timer_test::setUp(void)
{}

void Timer_test::tearDown(void)
{}

void Timer_test::tConstructor()
{
    auto t = pdEngine::Timer { 1 };
    (void)t;
    CPPUNIT_ASSERT(true);
}

