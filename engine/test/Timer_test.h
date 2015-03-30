#ifndef TIMER_TEST_H_
#define TIMER_TEST_H_

#include "Timer.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <string>

class Timer_test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Timer_test);
    CPPUNIT_TEST(tConstructor);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void tConstructor();

    private:
};

#endif /* TIMER_TEST_H_ */
