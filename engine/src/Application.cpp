/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"
#include "ApplicationImpl.h"
#include "Event.h"
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

        log->info("Initializing Appllicatoin");

        if (!setupTaskManager()) return false;
        if (!setupApplicationImpl()) return false;
        if (!setupEventManager()) return false;

        log->debug("Initializing main TaskManager");
        taskManager->init();

        // taskManager->addTask(std::make_shared(new InputManager(eventManager)));
        // taskManager->init();

        return(true);
    }

    bool Application::setupTaskManager()
    {
        return true;
    }

    bool Application::setupApplicationImpl()
    {
        auto log = GET_LOGGER();

        if ( pimpl->init() ) 
        {
            return true;
        }
        log->error("initialization failed");
        return false;
    }

    bool Application::setupEventManager()
    {
        auto log = GET_LOGGER();

        using namespace std::placeholders;

        EventListener listener = std::bind(&Application::onRequestQuit, this, _1);
        eventManager->addListener(ev_RequestQuit, listener);

        log->debug("Adding EventManager to main TaskManager");
        taskManager->addTask(eventManager);
        return true;
    }

    bool Application::start()
    {
        auto log = GET_LOGGER();

        log->debug("Starting main TaskManager");

        log->info("Entering main loop");
        auto i = 10;
        while (!doShutdown)
        {
            log->debug("Main loop");

            if (i == 5) eventManager->queueEvent(ev_RequestQuit);

            taskManager->updateTasks(1);

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
        GET_LOGGER()->debug("Recieved RequestQuit event, trying to do clean quit");
        shutdown();
        return true;
    }

}

