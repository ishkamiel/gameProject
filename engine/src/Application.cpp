/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"

#include "Logger.h"
#include "Timer.h"
#include "InputManagerSDL.h"

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

    bool Application::init(void)
    {
        auto log = MK_LOGGER();
        LOGGER_SET_DEBUG(log);

        // beforeInit();

        log->info("Initializing Appllication");

        log->info("creating TaskManager");
        taskManager = createTaskManager();
        log->info("creating EventManager");
        eventManager = createEventManager();
        log->info("creating InputManager");
        inputManager = createInputManager();
        log->info("creating Renderer");
        renderer = createRenderer();

        log->debug("Registering application level event listeners");
        registerListeners();

        log->debug("adding tasks to main TaskManager");
        taskManager->addTask(eventManager);
        taskManager->addTask(inputManager);
        taskManager->addTask(renderer);

        // beforeTaskInit();
        
        log->debug("Calling TaskManager->init() to initialize all subsystems");
        taskManager->initAll();

        if (taskManager->areAnyDead())
        {
            log->error("Some tasks failed initialization");
            return(false);
        }

        initOk = true;
        // afterInitDone();
        return(true);
    }

    bool Application::start(void)
    {
        if (!initOk) throw std::runtime_error("Applicatoin::start before successfull init");
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

    void Application::shutdown(void)
    {
        if (!doShutdown)
            throw std::runtime_error("shutdown() called while mainloop running");

        auto log = GET_LOGGER();

        log->info("Shutting down");

        // beforeShutdown();
        
        taskManager->abortAllNow();

        // afterTaskAbort();
        
        log->info("deleting Renderer");
        deleteRenderer();
        log->info("deleting InputManager");
        deleteInputManager();
        log->info("deleting EventManager");
        deleteEventManager();
        log->info("deleting TaskManager");
        deleteTaskManager();

        // afterShutdown();
    }

    InputManager_sptr  Application::getInputManager(void)
    {
        if (!inputManager)
            throw std::logic_error("getInputManager called before setupInputManager");
        return inputManager;
    }

    EventManager_sptr Application::getEventManager(void)
    {
        if (!eventManager)
            throw std::logic_error("getEventManager called before setupEventManager");
        return eventManager;
    }

    TaskManager_sptr Application::createTaskManager(void)
    {
        return std::make_shared<TaskManager>();
    }

    EventManager_sptr Application::createEventManager(void)
    {
        return std::make_shared<EventManager>();
    }

    InputManager_sptr Application::createInputManager(void)
    {
        return std::make_shared<InputManagerSDL>(getEventManager());
    }

    ResourceManager_sptr Application::createResourceManager(void)
    {
        return std::make_shared<ResourceManager>(getEventManager());
    }

    void Application::deleteResourceManager(void)
    {}

    void Application::deleteTaskManager(void)
    {}

    void Application::deleteRenderer(void)
    {}

    void Application::deleteEventManager(void)
    {}

    void Application::deleteInputManager(void)
    {}

    void Application::registerListeners(void)
    {
        using namespace std::placeholders;

        auto em = getEventManager();
        em->addListener(ev_RequestQuit, std::bind(&Application::onRequestQuit, this, _1));
        em->addListener(ev_Shutdown, std::bind(&Application::onShutdown, this, _1));
    }

    bool Application::onShutdown(Event_sptr e)
    {
        (void) e;
        GET_LOGGER()->debug("Recieved ev_Shutdown event, shutting down");
        doShutdown = true;
        return false;
    }

    bool Application::onRequestQuit(Event_sptr e)
    {
        (void) e;
        GET_LOGGER()->debug("Recieved ev_RequestQuit, sending ev_Shutdown");
        eventManager->queueEvent(ev_Shutdown);

        return true;
    }

}

