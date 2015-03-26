/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"
#include "ApplicationImpl.h"
#include "EventData.h"
#include "Logger.h"
#include "TaskManager.h"

#include <functional>
#include <memory>

namespace pdEngine
{
    Application::Application() :
        taskManager(new TaskManager()),
        eventManager(getEventManager()),
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
        auto log = MK_LOGGER();
        LOGGER_SET_DEBUG(log);

        log->info("Initializing pdEngine");

        if ( !pimpl->init() ) 
        {
            log->error("initialization failed");
            return false;
        }

        log->debug("Adding EventManager to main TaskManager");
        taskManager->addTask(eventManager);

        log->debug("Initializing main TaskManager");
        taskManager->init();

        //taskManager->addTask(std::make_shared(new InputManager(eventManager)));
        // taskManager->init();

        return(true);
    }

    EventManager_sptr Application::initEventManager()
    {
        // EventManager_sptr em = getEventManager();
        // auto listener = std::bind(&Application::shutdown, this);
        // using EventListener_sptr = std::shared_ptr<EventListener>;
        // using EventListener = std::function<bool(EventData_sptr)>;


        EventListener listener = [this](EventData_sptr a) {
            this.shtdown();
        } 

        auto ptr = std::make_shared<EventListener>(listener);
        em->addListener("QUIT", ptr);
        return em;
    }

    bool Application::start()
    {
        auto log = GET_LOGGER();

        log->debug("Starting main TaskManager");

        log->info("Entering main loop");
        auto i = 10;
        while (!doShutdown)
        {
            taskManager->updateTasks(1);
            if (i == 5) eventManager->queueEvent(std::make_shared<BaseEventData>("QUIT"));
            if (--i < 0) shutdown();
        }
        log->info("Leaving main loop");

        return(true);
    }

    void Application::shutdown()
	{
        GET_LOGGER()->info("Requesting shutdown");
        doShutdown = true;
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

    void Application::onQuit()
    {
        shutdown();
    }
    
}

