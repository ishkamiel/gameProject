#include "resources/SimpleResourceFile_test.h"
#include "Timer_test.h"

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

int main()
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(Timer_test::suite());
    runner.addTest(SimpleResourceFile_test::suite());

    runner.run();
    return(0);
}
