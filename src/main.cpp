#include "Logging/Logger.h"
#include "EventManager.h"
#include <iostream>

using pdLogger::log;
//using namespace pdLogger;
using pdLogger::LogLevel;

int main() 
{
    log(LogLevel::info, "Hello World!\n");
}
