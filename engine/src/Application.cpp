/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"

#include "utils/Logger.h"

#include "app/Config.h"
#include "events/EventManager.h"
#include "events/I_Event.h"
#include "events/DefaultEvent.h"
#include "input/InputManagerSDL.h"
#include "opengl/OpenglRenderer.h"
#include "renderer/SDLWindow.h"
#include "resources/ResourceManager.h"
#include "tasks/TaskManager.h"
#include "tasks/Task.h"
#include "utils/Timer.h"

#include <functional>
#include <memory>

namespace pdEngine {

Application::Application() {
}

Application::~Application() {
}

bool Application::init(void) {
    initializeLogging();

	v_preInit();
	PDE_INFO << "Starting application initialization sequence...";

    taskManager = std::make_shared<TaskManager>();
    initializeEventManager();
    initializeResourceManager();
	initializeWindow();
	initializeRenderer();

	PDE_DEBUG << "Initializing task manager tasks.";
    if (!taskManager->initAll()) {
	    PDE_FATAL << "Some tasks failed initialization.";
        return (false);
    }

    initOk = true;
	PDE_INFO << "Application successfully initialized!";

	v_postInit();
    return (true);
}

bool Application::start(void) 
{
    if (!initOk) {
	    PDE_FATAL << "Application not successfully initialized before start!";
	    exit(EXIT_FAILURE);
    }

    auto timer = Timer(updateFrequency);
	const int deltaTime = timer.getStepDeltaMs();

	PDE_INFO << "Entering main loop";
    while (!doShutdown) {

	    while (timer.step()) {
		    //auto deltaTime = timer.stepAndSleep();

		    taskManager->updateTasks(deltaTime);
	    }

        m_Renderer->v_Render();
		window->swapFrame();
    }

	PDE_INFO << "Leaving main loop after " << timer.totalSeconds() << " seconds";

    shutdown();
    return true;
}

std::shared_ptr<Config> Application::getConfig() noexcept
{
	return Config::get();
}

std::shared_ptr<EventManager> Application::getEventManager() noexcept
{
	return EventManager::get();
}

std::shared_ptr<ResourceManager> Application::getResourceManager() noexcept
{
	return ResourceManager::get();
}

void Application::shutdown(void) 
{
    if (!doShutdown)
        throw std::runtime_error("shutdown() called while main loop running");

	PDE_INFO << "Shutting down";

    taskManager->abortAllNow();

	m_Renderer.reset();
	window.reset();
	
	taskManager.reset();
}

void Application::initializeLogging(void) {
	setGlobalLogLevel(LogLevel::all);
}

void Application::initializeEventManager(void) {
	auto em = EventManager::get();

	taskManager->addTask(std::dynamic_pointer_cast<Task>(em));
	taskManager->addTask(std::make_shared<InputManagerSDL>());

	using namespace std::placeholders;

	// keep the handlers in static program lasting globals
	static auto quitHandler = em->addListener(ev_RequestQuit, std::bind(&Application::onRequestQuit, this, _1));
	static auto shutdownHandler = em->addListener(ev_Shutdown, std::bind(&Application::onShutdown, this, _1));
}

void Application::initializeResourceManager(void) {
	auto rm = ResourceManager::get();

	taskManager->addTask(std::shared_ptr<Task>(rm));
}

void Application::initializeWindow(void)
{
	PDE_INFO << "Creating and opening main window.";
	auto w = std::make_shared<SDLWindow>();
	w->onInit();

	taskManager->addTask(w);
	window = w;
	window->openWindow();
}

void Application::initializeRenderer(void)
{
	PDE_INFO << "Initializing rendering.";

	m_Renderer = window->createRenderer();

	m_Renderer->onInit();

	taskManager->addTask(m_Renderer);
}

bool Application::onShutdown(Event_sptr e) {
	(void) e;
	PDE_DEBUG << "Received ev_Shutdown event, shutting down";
	doShutdown = true;
	return false;
}

bool Application::onRequestQuit(Event_sptr e) {
	(void) e;
	PDE_DEBUG << "Received ev_RequestQuit, sending ev_Shutdown";
	EventManager::get()->queueEvent(std::make_shared<DefaultEvent>(ev_Shutdown));
	return true;
}

}
