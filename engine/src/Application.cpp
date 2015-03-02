/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"
#include "GraphicsOgre.h"

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
        log()->info("Initializing pdEngine..");

        if (! initGraphics());

        return(true);
    }

    bool Application::start()
    {
        log()->info("Exiting pdEngine...");
        return(true);
    }
    
    void Application::shutdown()
	{
	}

    bool Application::initGraphics()
    {
        graphicsEngine = std::make_shared<GraphicsOgre>();
        graphicsEngine->init();

        return(true);
    }
}

