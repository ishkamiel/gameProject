#include "DemoOpengl.h"

#include "app/Config.h"

#include <iostream>

int main(int argc, char** argv)
{
    if (!pdEngine::Config::get()->init(argc, argv)) {
        exit(EXIT_FAILURE);
    }

    try {
        pdEngineDemo::DemoOpengl app {};


        if (app.init())
        {
            app.start();
            return(0);
        }
        std::cout << "Whoops, app initialization failed...\n";
        return(-1);
    }
    catch (std::exception& e)
    {
        std::cerr << "Uncaught exception: " << e.what() << "\n";
    }

    return 0;
}
