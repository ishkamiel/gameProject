#include "Strings_test.h"

void StringsTests::setUp(void)
{
	simpleString = c_simpleString;
}

void StringsTests::tearDown(void)
{
}

void StringsTests::checkStrings(const std::string& expected, const std::string& actual)
{
	CPPUNIT_ASSERT_EQUAL(expected, actual);
}

void StringsTests::testFormaters(std::string expected, std::string input) 
{
    CPPUNIT_ASSERT_EQUAL(expected, pdUtils::getFormatedString(input));
    CPPUNIT_ASSERT_EQUAL(expected, pdUtils::formatString(input));
}

template<typename ... Targs>
void StringsTests::testFormaters(std::string expected, std::string input, Targs... args)
{
    CPPUNIT_ASSERT_EQUAL(expected, pdUtils::getFormatedString(input, args...));
    CPPUNIT_ASSERT_EQUAL(expected, pdUtils::formatString(input, args...));
}


void StringsTests::test_getFormatedString()
{
	std::string checkValue;
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString));
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString, 1));
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString, 1, 2));
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString, 1, 2, 3));
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString, 1.0, 2, "error", 'c'));
    checkStrings("%", pdUtils::getFormatedString("%%"));
    checkStrings("%%%", pdUtils::getFormatedString("%%%%%%"));
	checkStrings("three:3", pdUtils::getFormatedString("three:%d", 3));
	checkStrings("three:3,four:4", pdUtils::getFormatedString("three:%d,four:%d", 3, 4));
	checkStrings("three:3,four:4,five:5", pdUtils::getFormatedString("three:%d,four:%d,five:%d", 3, 4, 5));
}


void StringsTests::test_formatString()
{
	pdUtils::formatString(simpleString);
	CPPUNIT_ASSERT(c_simpleString == simpleString);
	pdUtils::formatString(simpleString, 1);
	CPPUNIT_ASSERT(c_simpleString == simpleString);
	pdUtils::formatString(simpleString, 1, 2);
	CPPUNIT_ASSERT(c_simpleString == simpleString);
	pdUtils::formatString(simpleString, 1, 2, 3);
	CPPUNIT_ASSERT(c_simpleString == simpleString);
	pdUtils::formatString(simpleString, 'c', 2.0, "error");
	CPPUNIT_ASSERT(c_simpleString == simpleString);
}

void StringsTests::test_formatStringComplex()
{
	std::string inputString { "float:%f,%%%%,hundred:%i%%---" };
	std::string expectedValue { "float:%f,%%,hundred:%i%---" };

    testFormaters("%%", "%%%%");
    testFormaters(expectedValue, inputString);

    testFormaters("100%", "%i%%", 100);
    testFormaters("%100%", "%%%i%%", 100);

	expectedValue = "float:1.23456,%%,hundred:100%---";
    testFormaters(expectedValue, inputString, 1.23456, 100);
}

