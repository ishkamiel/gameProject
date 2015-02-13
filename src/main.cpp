#include "Logging/Logger.h"
#include "EventManager.h"
#include <iostream>

int main() 
{
    auto logger = pdLogger::getLogger();
    logger->info("this should not work, yet: %d\n", 1.10);
    /*
    logger->log(pdLogger::LogLevel::info, "Hello World!\n");
    logger->warn("oh no, warning\n");
    logger->info("some info\n");
    logger->debug("debugging\n");
    logger->error("and an error\n");
    */

}
