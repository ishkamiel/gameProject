#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Event.h"
#include "EventManager.h"
#include "InputManager.h"
#include "TaskManager.h"
#include "renderer/Renderer.h"

#include <memory>

namespace pdEngine
{
	class Application
	{
        TimerFrequency                  updateFrequency {240};

        InputManager_sptr               inputManager;  
		EventManager_sptr 				eventManager;
		TaskManager_sptr                taskManager;
        Renderer_sptr                   renderer;

        bool initOk                     { false };
        bool doShutdown                 { false };

	public:
		Application();
		virtual ~Application();

        void addSubsystem(Task_sptr);

		bool init();
		bool start();
		EventManager_sptr getEventManager();
        InputManager_sptr getInputManager();

    protected:
        virtual TaskManager_sptr createTaskManager(void);
        virtual EventManager_sptr createEventManager(void);
        virtual Renderer_sptr createRenderer(void) =0;
        virtual InputManager_sptr createInputManager(void);

        virtual void deleteTaskManager(void);
        virtual void deleteEventManager(void);
        virtual void deleteRenderer(void);
        virtual void deleteInputManager(void);

	private:
		void shutdown();
        void registerListeners(void);
        bool onShutdown(Event_sptr e);
        bool onRequestQuit(Event_sptr e);
	};
}

#endif
