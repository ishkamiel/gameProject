#include "Application.h"

#include "Logger.h"

int main(int argc, char **argv)
{
    auto log = pdLogger::getLogger();
    log->info("Logging is on!");

	auto mainWindow = pdGame::getMainWindow("pdGame demo");
	mainWindow->initialize(&argc, argv);
	log->info("mainWindow initialized");
	mainWindow->start();

	return(0);
}
