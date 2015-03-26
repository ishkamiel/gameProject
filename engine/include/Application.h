#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Event.h"
#include "EventManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "TaskManager.h"

#include <memory>

namespace pdEngine
{
	class Application
	{
        TimerFrequency                  updateFrequency {240};

		TaskManager_sptr                taskManager;
        Renderer_sptr                   renderer;

        bool doShutdown { false };

	public:
		Application();
		virtual ~Application();

        void addSubsystem(Task_sptr);

		bool init();
		bool start();
		void shutdown();

    protected:
        virtual bool setupTaskManager(void);
        virtual void shutdownTaskManager(void);
        virtual bool setupRenderer(void);
        virtual void shutdownRenderer(void);
        virtual bool setupEventManager(void);
        virtual void shutdownEventManager(void);
        virtual bool setupInputManager(void);
        virtual void shutdownInputManager(void);

	private:
        void registerListeners(void);
        bool onShutdown(Event_sptr e);
        bool onRequestQuit(Event_sptr e);
	};
}

#endif
