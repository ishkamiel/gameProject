#include "Logger.h"
#include "EventManager.h"
#include <iostream>

using pdGame::log;

int main() 
{
    log(pdGame::LogLevel.info, "Hello World!\n");
}
