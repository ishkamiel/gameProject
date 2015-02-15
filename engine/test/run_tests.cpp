
#include "utils/Strings_test.h"

#include <cppunit/ui/text/TestRunner.h>

int main()
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest( StringsTests::suite() );
	runner.run();
	return (0);
} 
