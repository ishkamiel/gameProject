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

        if ( !setupTaskManager()
                || !setupEventManager() 
                || !setupInputManager() 
                || !setupRenderer())
            return false;

        log->info("Registering application level event listeners");
        registerListeners();

        log->debug("Calling TaskManager->init() to initialize all subsystems");
        taskManager->init();

        if (taskManager->areAnyDead())
        {
            log->error("Some tasks failed initialization");
            return(false);
        }

        initOk = true;
        return(true);
   }

    bool Application::start()
    {
        if (!initOk) throw std::string("Applicatoin::start before successfull init");
        auto log = GET_LOGGER();

        auto timer = new Timer(updateFrequency);
        log->info("Entering main loop");
        while (!doShutdown)
        {
            auto deltaTime = timer->stepAndSleep();

            taskManager->updateTasks(deltaTime);

            renderer->render();
        }
        log->info("Leaving main loop after {0} milliseconds", timer->totalMilliseconds());
        delete timer;

        shutdown();
        return true;
    }

    void Application::shutdown()
    {
        GET_LOGGER()->info("Shutting down");
        shutdownRenderer();
        shutdownInputManager();
        shutdownEventManager();
        shutdownTaskManager();
    }

    InputManager_sptr  Application::getInputManager()
    {
        if (!inputManager)
            throw "getInputManager called before setupInputManager";
        return inputManager;
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
        inputManager.reset(new InputManagerSDL(getEventManager()));
        log->debug("Created InputManager");

        taskManager->addTask(inputManager);
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

        em->addListener(ev_Shutdown,
                std::bind(&Application::onShutdown, this, _1));
    }

    bool Application::onShutdown(Event_sptr e)
    {
        (void) e;
        GET_LOGGER()->debug("Recieved Shutdown event, shutting down");
        doShutdown = true;
        return false;
    }

    bool Application::onRequestQuit(Event_sptr e)
    {
        (void) e;
        GET_LOGGER()->debug("Recieved RequestQuit event");
        eventManager->queueEvent(ev_Shutdown);

        return true;
    }

}

