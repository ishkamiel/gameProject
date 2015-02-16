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
	checkStrings(c_simpleString, pdUtils::getFormatedString(simpleString));
	checkStrings(c_simpleString, pdUtils::getFormatedString(simpleString, 1));
	checkStrings(c_simpleString, pdUtils::getFormatedString(simpleString, 1, 2));
	checkStrings(c_simpleString, pdUtils::getFormatedString(simpleString, 1, 2, 3));
	checkStrings(c_simpleString, pdUtils::getFormatedString(simpleString, 1.0, 2, "error", 'c'));

    checkStrings("%", pdUtils::getFormatedString("%%"));
    checkStrings("%%%", pdUtils::getFormatedString("%%%%%%"));
	checkStrings("three:3", pdUtils::getFormatedString("three:%d", 3));
	checkStrings("three:3,four:4", pdUtils::getFormatedString("three:%d,four:%d", 3, 4));
	checkStrings("three:3,four:4,five:5", pdUtils::getFormatedString("three:%d,four:%d,five:%d", 3, 4, 5));

	checkStrings("123", pdUtils::getFormatedString("1%i3" , 2));
	checkStrings("%something%", pdUtils::getFormatedString("%%%s%%" , "something"));
	checkStrings("abc", pdUtils::getFormatedString("%c%c%c" , 'a', 'b', 'c'));
}


void StringsTests::test_formatString()
{
    std::string tmp { "" };

	checkStrings(c_simpleString, pdUtils::formatString(simpleString));
	checkStrings(c_simpleString, pdUtils::formatString(simpleString, 1));
	checkStrings(c_simpleString, pdUtils::formatString(simpleString, 1, 2));
	checkStrings(c_simpleString, pdUtils::formatString(simpleString, 1, 2, 3));
	checkStrings(c_simpleString, pdUtils::formatString(simpleString, 'c', 2.0, "error"));

    checkStrings("%", pdUtils::formatString(tmp = "%%"));
    checkStrings("%%%", pdUtils::formatString(tmp = "%%%%%%"));
	checkStrings("three:3", pdUtils::formatString(tmp = "three:%d", 3));
	checkStrings("three:3,four:4", pdUtils::formatString(tmp = "three:%d,four:%d", 3, 4));
	checkStrings("three:3,four:4,five:5", pdUtils::formatString(tmp = "three:%d,four:%d,five:%d", 3, 4, 5));

	checkStrings("123", pdUtils::formatString(tmp = "1%i3" , 2));
	checkStrings("%something%", pdUtils::formatString(tmp = "%%%s%%" , "something"));
	checkStrings("abc", pdUtils::formatString(tmp = "%c%c%c" , 'a', 'b', 'c'));
}

void StringsTests::test_formatStringComplex()
{
	std::string inputString { "float:%f,%%%%,hundred:%i%%---" };
	std::string expectedValue { "float:%f,%%,hundred:%i%---" };

    testFormaters("%%", "%%%%");
    testFormaters("%%", "%%%");
    testFormaters(expectedValue, inputString);

    testFormaters("100%", "%i%%", 100);
    testFormaters("%100%", "%%%i%%", 100);

	expectedValue = "float:1.23456,%%,hundred:100%---";
    testFormaters(expectedValue, inputString, 1.23456, 100);

    testFormaters("%%1.11%%123%", "%%%%%f%%%%%i%d%i%%", 1.11, 1, 2, 3);
    testFormaters("%A%1.11%%123%percent%", "%%%c%%%f%%%%%i%d%i%%%s%%", 'A', 1.11, 1, 2, 3, "percent");
}

