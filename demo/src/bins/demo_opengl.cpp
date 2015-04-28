#include "DemoOpengl.h"

#include <iostream>

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

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
