#include "../src/logging/Logger.h"

int main()
{
    auto log = pdLogger::getLogger();
    log->info("Logging is on!");
}
