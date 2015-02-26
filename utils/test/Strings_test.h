#ifndef PD_STRING_TEST_H
#define PD_STRING_TEST_H

#include "pdStrings.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string>

class StringsTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(StringsTests);
    CPPUNIT_TEST(test_getFormatedString);
    CPPUNIT_TEST(test_formatString);
    CPPUNIT_TEST(test_formatStringComplex);
    CPPUNIT_TEST(test_trim);
    CPPUNIT_TEST(test_trimNewline);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void test_getFormatedString();
        void test_formatString();
        void test_formatStringComplex();
        void test_trim();
        void test_trimNewline();

    private:
        void checkStrings(const std::string&, const std::string&);

        void testFormaters(std::string, std::string);

        template<typename ... Targs>
        void testFormaters(std::string, std::string, Targs... args);

        const std::string c_simpleString = "All Your Base Are Belong to Us";
        std::string simpleString;
};

#endif
