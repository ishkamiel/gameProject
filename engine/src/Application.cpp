/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"
#include "Event.h"
#include "InputManagerSDL.h"
#include "Logger.h"
#include "RendererSDL.h"
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
        if (!setupRenderer()) return false;
		
		log->info("Registering application level event listeners");
		registerListeners();

        log->debug("Calling TaskManager->init() to initialize all subsystems");
        taskManager->init();

        return(true);
    }

    void Application::shutdown()
    {
        GET_LOGGER()->info("Shutting down");
        shutdownRenderer();
        shutdownInputManager();
        shutdownEventManager();
        shutdownTaskManager();
        doShutdown = true;
    }

    bool Application::start()
    {
        auto log = GET_LOGGER();

        auto timer = new Timer(updateFrequency);
        log->info("Entering main loop");
        while (!doShutdown)
        {
            auto deltaTime = timer->stepAndSleep();
            //DLOG("Main loop, timeDelta: {0}", deltaTime);

            taskManager->updateTasks(deltaTime);

            renderer->render();
        }
        log->info("Leaving main loop after {0} milliseconds", timer->totalMilliseconds());
        delete timer;

        return(true);
    }
    
    EventManager_sptr Application::getEventManager()
	{
		if (!eventManager)
			throw "getEventManager called before setupEventManager";
		return eventManager;
	}

    bool Application::setupTaskManager()
    {
        auto log = GET_LOGGER();
        taskManager.reset(new TaskManager());
        log->debug("Created TaskManager");

        return true;
    }

    void Application::shutdownTaskManager()
    {}

    bool Application::setupRenderer()
    {
        auto log = GET_LOGGER();
        renderer.reset(new RendererSDL());
        log->debug("Created RendererSDL");


        taskManager->addTask(renderer);
        log->debug("RenderSDL added to main TaskManager");
        return true;
    }

    void Application::shutdownRenderer()
    {}

    bool Application::setupEventManager()
    {
        auto log = GET_LOGGER();
		eventManager.reset(new EventManager());
        log->debug("Created EventManager");

        taskManager->addTask(eventManager);
        log->debug("EventManager added to main TaskManager");
        return true;
    }

    void Application::shutdownEventManager()
    {}

    bool Application::setupInputManager()
    {
        auto log = GET_LOGGER();
        auto im = std::make_shared<InputManagerSDL>(getEventManager());
        log->debug("Created InputManager");

        taskManager->addTask(im);
        log->debug("InputManagerladded to main TaskManager");
        return true;
    }

    void Application::shutdownInputManager()
    {}

    void Application::registerListeners(void)
    {
        auto log = GET_LOGGER();
        auto em = getEventManager();

        using namespace std::placeholders;
        EventListener listener = std::bind(&Application::onRequestQuit, this, _1);
        em->addListener(ev_RequestQuit, listener);
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

