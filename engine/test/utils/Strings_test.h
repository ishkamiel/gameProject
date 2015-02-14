#ifndef PD_STRING_TEST_H
#define PD_STRING_TEST_H

#include "../../src/utils/Strings.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string>

class TestStrings : public CppUnit::TestFixture  
{
    CPPUNIT_TEST_SUITE(TestStrings);
    CPPUNIT_TEST(test_getFormatedString);
    CPPUNIT_TEST(test_formatString);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void test_getFormatedString();
        void test_formatString();

    private:
        const std::string c_simpleString = "All Your Base Are Belong to Us";
        std::string simpleString;
};

#endif
