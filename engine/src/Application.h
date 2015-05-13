#pragma once

#include "renderer/I_Renderer.h"
#include "renderer/I_Window.h"	

#include <memory>
#include <list>

namespace pdEngine {

class ResourceManager;
class TaskManager;
class Config;
class EventManager;
class I_Event;

class Application {
	int updateFrequency{250};

	Renderer_sptr m_Renderer;
	Window_sptr window;
	std::shared_ptr<TaskManager> taskManager;

	bool initOk { false };
	bool doShutdown { false };
	bool m_LogToConsole { true };

public:
    Application();
    virtual ~Application();

    bool init(void);
    bool start(void);

	std::shared_ptr<Config> getConfig() noexcept;
	std::shared_ptr<EventManager> getEventManager() noexcept;
	std::shared_ptr<ResourceManager> getResourceManager() noexcept;

protected:
	//! Runs before initialization of base systems
	virtual void v_preInit(void) {};

	//! Runs when all base systems are running
    virtual void v_postInit(void) {};

private:
    void initializeLogging(void);
    void initializeEventManager(void);
    void initializeResourceManager(void);
    void initializeWindow(void);
    void initializeRenderer(void);

    void shutdown(void);
    bool onShutdown(std::shared_ptr<I_Event> e);
    bool onRequestQuit(std::shared_ptr<I_Event> e);

};
}

