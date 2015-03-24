/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"
#include "ApplicationImpl.h"
#include "TaskManager.h"

#include "spdlog/spdlog.h"

namespace pdEngine
{
    Application::Application() :
        taskManager(new TaskManager()),
        eventManager(new EventManager()),
        pimpl(new ApplicationImpl())
    {}

    Application::~Application()
    {}

    void Application::addSubsystem(Task_sptr ptr)
    {
        taskManager->addTask(ptr);
    }

    bool Application::init()
    {
        auto logger = spdlog::stderr_logger_mt("pdengine");
        logger->info("Initializing pdEngine application..");
        pimpl->init();
        // eventManager->init();
        taskManager->init();

        return(true);
    }

    bool Application::start()
    {
        spdlog::get("pdengine")->info("Starting pdEngine application...");
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

