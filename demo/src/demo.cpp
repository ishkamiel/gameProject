#include "DemoApplication.h"

#include "app/Config.h"

#include <iostream>

int main(int argc, char **argv)
{
	if (!pdEngine::Config::get()->init(argc, argv)) {
		exit(EXIT_FAILURE);
	}

	pdEngineDemo::DemoApplication app{};

	if (app.init()) {
		app.start();
		return (0);
	}

	std::cout << "Whoops, app initialization failed...\n";
	return (-1);
}

