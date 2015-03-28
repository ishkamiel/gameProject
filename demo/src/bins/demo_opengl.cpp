#include "DemoOpengl.h"

#include <iostream>

int main()
{
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

}
