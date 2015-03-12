/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"

namespace pdEngine
{
    Application::Application() :
        taskManager(new TaskManager()),
        eventManager(new EventManager())
    {}

    Application::~Application()
    {}

    bool Application::init()
    {
        log()->info("Initializing pdEngine application..");

        return(true);
    }

    bool Application::start()
    {
        log()->info("Starting pdEngine application...");
        return(true);
    }
    
    void Application::shutdown()
	{
	}

    bool Application::initGraphics()
    {
        return(true);
    }
}

