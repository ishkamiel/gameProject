/*
 * Applicatoin.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#include "Application.h"

#include "Logger.h"
#include "Root.h"

#include "events/EventManager.h"
#include "opengl/OpenglRenderer.h"
#include "renderer/SDLWindow.h"
#include "resources/ResourceManager.h"
#include "Utils.h"
#include "Timer.h"
#include "input/InputManagerSDL.h"

#include <functional>
#include <memory>

namespace pdEngine {

Application::Application() {
}

Application::~Application() {
}

bool Application::init(void) {
    initializeLogging();

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
	auto em = EventManager::getSingleton();
	getRoot()->setEventManager(em);

	taskManager->addTask(std::dynamic_pointer_cast<Task>(em));
	taskManager->addTask(std::make_shared<InputManagerSDL>(em));

	using namespace std::placeholders;

	em->addListener(ev_RequestQuit, std::bind(&Application::onRequestQuit, this, _1));
	em->addListener(ev_Shutdown, std::bind(&Application::onShutdown, this, _1));
}

void Application::initializeResourceManager(void) {
	auto rm = std::make_shared<ResourceManager>();
	getRoot()->setResourceManager(rm);

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
	EventManager::getSingleton()->queueEvent(ev_Shutdown);
	return true;
}

}
