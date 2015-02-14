#include "Strings_test.h"

void TestStrings::setUp(void)
{
    simpleString = c_simpleString;
}

void TestStrings::tearDown(void)
{
}

void TestStrings::test_getFormatedString()
{
    CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString));
}


void TestStrings::test_formatString()
{
    pdUtils::formatString(simpleString);
    CPPUNIT_ASSERT(c_simpleString == simpleString);
}
