#pragma once

#include "tasks/TaskManager.h"
#include "tasks/Task.h"
#include "renderer/I_Renderer.h"	
#include "renderer/I_Window.h"	

#include <memory>
#include <list>

namespace pdEngine {

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
    void shutdown(void);
    bool onShutdown(Event_sptr e);
    bool onRequestQuit(Event_sptr e);

    TimerFrequency updateFrequency{240};

    Renderer_sptr renderer;
    Window_sptr window;
    TaskManager_sptr taskManager;

    bool initOk{false};
    bool doShutdown{false};
    bool m_LogToConsole { true };
};
}

