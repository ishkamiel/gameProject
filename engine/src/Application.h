#pragma once

#include "tasks/TaskManager.h"
#include "tasks/Task.h"
#include "renderer/I_Renderer.h"	
#include "renderer/I_Window.h"	

#include <memory>
#include <list>

namespace pdEngine {

class ResourceManager;
using ResourceManager_sptr = std::shared_ptr<ResourceManager>;

class Application {
public:
    Application();
    virtual ~Application();

    bool init(void);
    bool start(void);

protected:

private:
    void initializeLogging(void);
    void initializeEventManager(void);
    void initializeResourceManager(void);
    void initializeWindow(void);
    void initializeRenderer(void);

    void shutdown(void);
    bool onShutdown(Event_sptr e);
    bool onRequestQuit(Event_sptr e);

    int updateFrequency{250};

    Renderer_sptr m_Renderer;
    Window_sptr window;
    TaskManager_sptr taskManager;

    bool initOk{false};
    bool doShutdown{false};
    bool m_LogToConsole { true };
};
}

