/*
 * Demo.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "DemoApplication.h"

#include <iostream>

int main()
{
    try {
        pdEngineDemo::DemoApplication app {};

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
