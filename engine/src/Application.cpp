/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"
#include "ApplicationImpl.h"
#include "Event.h"
#include "InputManagerSDL.h"
#include "Logger.h"
#include "TaskManager.h"
#include "Timer.h"

#include <functional>
#include <memory>

namespace pdEngine
{
    Application::Application() 
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

        log->info("Initializing Appllication");

        if (!setupTaskManager()) return false;
        if (!setupEventManager()) return false;
        if (!setupInputManager()) return false;
        if (!setupApplicationImpl()) return false;

        log->debug("Initializing main TaskManager");
        taskManager->init();

        return(true);
    }

    bool Application::setupTaskManager()
    {
        auto log = GET_LOGGER();
        taskManager.reset(new TaskManager());

        log->debug("TaskManager setup ok");
        return true;
    }

    bool Application::setupApplicationImpl()
    {
        auto log = GET_LOGGER();
        pimpl.reset(new ApplicationImpl());

        if ( !pimpl->init() ) 
        {
            log->error("initialization failed");
            return false;
        }
        log->debug("ApplicationImpl setup ok");
        return true;
    }

    bool Application::setupEventManager()
    {
        auto log = GET_LOGGER();
        eventManager = getEventManager();
        eventManager.reset(new EventManager());

        using namespace std::placeholders;
        EventListener listener = std::bind(&Application::onRequestQuit, this, _1);
        eventManager->addListener(ev_RequestQuit, listener);

        log->debug("Adding EventManager to main TaskManager");
        taskManager->addTask(eventManager);
        return true;
    }

    bool Application::setupInputManager()
    {
        auto log = GET_LOGGER();
        inputManager.reset(new InputManagerSDL(eventManager));

        log->debug("Adding InputManager to main TaskManager");
        taskManager->addTask(inputManager);
        return true;
    }

    bool Application::start()
    {
        auto log = GET_LOGGER();

        //auto start = now();
        auto i = 10;

        auto timer = new Timer(updateFrequency);
        log->info("Entering main loop");
        while (!doShutdown)
        {
            auto deltaTime = timer->step();

            log->debug("Main loop, timeDelta: {}", deltaTime);

            if (i == 5) eventManager->queueEvent(ev_RequestQuit);

            taskManager->updateTasks(deltaTime);

            if (--i < 0) shutdown();
        }
        log->info("Leaving main loop");
        delete timer;

        return(true);
    }

    void Application::shutdown()
    {
        GET_LOGGER()->info("Requesting shutdown");
        doShutdown = true;
    }

    bool Application::onShutdown(Event_sptr e)
    {
        (void) e;
        GET_LOGGER()->debug("Recieved Shutdown event, shutting down");
        shutdown();
        return true;
    }

    bool Application::onRequestQuit(Event_sptr e)
    {
        (void) e;
        GET_LOGGER()->debug("Recieved RequestQuit event, trying to do do a clean shutdown");
        shutdown();
        return true;
    }

}

