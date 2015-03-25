/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"
#include "ApplicationImpl.h"
#include "Logger.h"
#include "TaskManager.h"

#include <memory>

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
        auto logger = MK_LOGGER();
        LOGGER_SET_DEBUG(logger);

        logger->info("Initializing pdEngine application..");

        if ( !pimpl->init() ) 
        {
            return false;
        }
        //taskManager->addTask(std::make_shared(new InputManager(eventManager)));
        // eventManager->init();
        // taskManager->init();

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

    InputManager_sptr Application::getInputManager()
    {
        return nullptr;
        //return std::make_shared<InputManager>(new InputManager(eventManager));
    }

    bool Application::initGraphics()
    {
        return(true);
    }
}

