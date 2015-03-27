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
    pdEngineDemo::DemoApplication app {};

    if (app.init())
    {
        app.start();
        return(0);
    }
    std::cout << "Whoops, we died...\n";
    return(-1);
}
