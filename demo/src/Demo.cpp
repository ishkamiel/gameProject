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
    app.init();
    app.start();
    return(0);
}
