#include "Timer_test.h"
#include "Timer.h"

void Timer_test::setUp(void) {}
void Timer_test::tearDown(void) {};

void Timer_test::tConstructor()
{
    auto t = pdEngine::Timer { 1 };
    (void)t;
    CPPUNIT_ASSERT(true);
}
