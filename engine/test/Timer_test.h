// #include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

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
};
