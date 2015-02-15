#include "Strings_test.h"

/*
template<>
struct CppUnit::assertion_traits<std::string>   // specialization for the std::string type
{
		static bool equal( const std::string& x, const std::string& y )
		{
			return (x == y);
		}

		static std::string toString( const std::string& x )
		{
			std::string text = '"' + x + '"';    // adds quote around the string to see whitespace
			OStringStream ost;
			ost << text;
			return (ost.str());
		}
};
*/

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

void StringsTests::test_getFormatedString()
{
	std::string checkValue;
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString));
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString, 1));
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString, 1, 2));
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString, 1, 2, 3));
	CPPUNIT_ASSERT(c_simpleString == pdUtils::getFormatedString(simpleString, 1.0, 2, "error", 'c'));
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

	checkStrings(expectedValue, pdUtils::getFormatedString(inputString));
	checkStrings(expectedValue, pdUtils::formatString(inputString));

	expectedValue = "float:1.23456,%%,hundred:100%---";
	checkStrings(expectedValue, pdUtils::getFormatedString(inputString, 1.23456, 100));
	checkStrings(expectedValue, pdUtils::formatString(inputString, 1.123456, 100));
}

