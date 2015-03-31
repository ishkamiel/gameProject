/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"

#include "Utils.h"
#include "Timer.h"
#include "InputManagerSDL.h"

#include <functional>
#include <memory>

namespace pdEngine
{
    Application::Application() 
    {
    }

    Application::~Application()
    {}

    void Application::addSubsystem(Task_sptr ptr)
    {
        taskManager->addTask(ptr);
    }

    bool Application::init(void)
    {
        initLogging();
        auto log = getLogger();

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
        if (!taskManager->initAll())
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
        auto log = getLogger();

        if (!initOk) throw std::runtime_error("Applicatoin::start before successfull init");

        auto timer = new Timer(updateFrequency);
        log->info("Entering main loop");
        while (!doShutdown)
        {
            auto deltaTime = timer->stepAndSleep();

            taskManager->updateTasks(deltaTime);

            renderer->render();
        }
        log->info("Leaving main loop after {0} milliseconds", timer->totalMilli());
        delete timer;

        shutdown();
        return true;
    }

    void Application::shutdown(void)
    {
        auto log = getLogger();
        if (!doShutdown)
            throw std::runtime_error("shutdown() called while mainloop running");

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

    void Application::initLogging(void)
    {
        if (true)
        {
            std::shared_ptr<spdlog::logger> log { 
                spdlog::stderr_logger_mt("pdengine")
            };
            setLogger(log);
        }
        else
        {
            size_t q_size = 1048576; //queue size must be power of 2
            spdlog::set_async_mode(q_size);
            std::shared_ptr<spdlog::logger> log { 
                spdlog::daily_logger_mt("pdengine", "pdeninge") };
            setLogger(log);
        }

        getLogger()->set_level(spdlog::level::debug);
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
        //return std::make_shared<ResourceManager>(getEventManager());
        return nullptr;
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
        DLOG("Recieved ev_Shutdown event, shutting down");
        doShutdown = true;
        return false;
    }

    bool Application::onRequestQuit(Event_sptr e)
    {
        (void) e;
        DLOG("Recieved ev_RequestQuit, sending ev_Shutdown");
        eventManager->queueEvent(ev_Shutdown);
        return true;
    }

}

