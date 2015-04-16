/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"

#include "events/EventManager.h"
#include "renderer/OpenglRenderer.h"
#include "renderer/SDLWindow.h"
#include "resources/ResourceManager.h"
#include "Logger.h"
#include "Utils.h"
#include "Timer.h"
#include "InputManagerSDL.h"

#include <functional>
#include <memory>

namespace pdEngine {

Application::Application() {
}

Application::~Application() {
}

bool Application::init(void) {
    initializeLogging();
    auto log = getLogger();

    log->info("Starting application initialization sequence...");

    taskManager = std::make_shared<TaskManager>();
    initializeEventManager();
    initializeResourceManager();

    log->debug("Initializing task manager tasks.");
    if (!taskManager->initAll()) {
        log->error("Some tasks failed initialization.");
        return (false);
    }

    log->info("Creating and opening main window.");
	window = std::make_shared<SDLWindow>();
	window->init();
	window->openWindow();

	log->info("Initializing rendering.");
    renderer = window->getRenderer();

    initOk = true;
	log->info("Application successfully initialized!");
    return (true);
}

bool Application::start(void) 
{
    auto log = getLogger();

    if (!initOk) throw std::runtime_error("Application not successfully initialized before start!");

    auto timer = new Timer(updateFrequency);
    log->info("Entering main loop");
    while (!doShutdown) {
        auto deltaTime = timer->stepAndSleep();

        taskManager->updateTasks(deltaTime);

        renderer->render();

		window->swapFrame();
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
        throw std::runtime_error("shutdown() called while main loop running");

    log->info("Shutting down");

    taskManager->abortAllNow();

	renderer.reset();
	window.reset();
	
	taskManager.reset();
}

void Application::initializeLogging(void) {
	/*
	if (m_LogToConsole) {
		std::shared_ptr<spdlog::logger> log{
			spdlog::stderr_logger_mt("pdengine")
		};
		log->set_level(spdlog::level::debug);
		setLogger(log);
	} else {
		size_t q_size = 1048576; //queue size must be power of 2
		spdlog::set_async_mode(q_size);
		std::shared_ptr<spdlog::logger> log{
			spdlog::daily_logger_mt("pdengine", "pdengine")
		};
		setLogger(log);
	}
	 */

	auto l = getLogger();
}

void Application::initializeEventManager(void) {
	auto em = EventManager::getSingleton();
	taskManager->addTask(std::dynamic_pointer_cast<Task>(em));
	taskManager->addTask(std::make_shared<InputManagerSDL>(em));

	using namespace std::placeholders;

	em->addListener(ev_RequestQuit, std::bind(&Application::onRequestQuit, this, _1));
	em->addListener(ev_Shutdown, std::bind(&Application::onShutdown, this, _1));
}

void Application::initializeResourceManager(void) {
	auto rm = std::make_shared<ResourceManager>();

	taskManager->addTask(std::shared_ptr<Task>(rm));
}

bool Application::onShutdown(Event_sptr e) {
	(void) e;
	PD_debug("Received ev_Shutdown event, shutting down");
	doShutdown = true;
	return false;
}

bool Application::onRequestQuit(Event_sptr e) {
	(void) e;
	PD_debug("Received ev_RequestQuit, sending ev_Shutdown");
	EventManager::getSingleton()->queueEvent(ev_Shutdown);
	return true;
}

}
