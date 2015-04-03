#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "tasks/TaskManager.h"
#include "tasks/Task.h"
#include "renderer/I_Renderer.h"	
#include "renderer/I_Window.h"	

#include <memory>
#include <list>

namespace pdEngine {

class Application {
    TimerFrequency updateFrequency{240};

    Renderer_sptr renderer;
    Window_sptr window;
    TaskManager_sptr taskManager;

    bool initOk{false};
    bool doShutdown{false};

public:
    Application();
    virtual ~Application();

    bool init(void);
    bool start(void);

protected:

private:
    void initLogging(void);
    void initializeEventManager(void);
    void shutdown(void);
    bool onShutdown(Event_sptr e);
    bool onRequestQuit(Event_sptr e);
};
}

#endif