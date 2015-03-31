#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "InputManager.h"
#include "events/iEvent.h"
#include "events/EventManager.h"
#include "tasks/TaskManager.h"
#include "resources/ResourceManager.h"
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

		bool init(void);
		bool start(void);
		EventManager_sptr getEventManager(void);
        InputManager_sptr getInputManager(void);

    protected:
        virtual void initLogging(void);

        virtual TaskManager_sptr createTaskManager(void);
        virtual EventManager_sptr createEventManager(void);
        virtual Renderer_sptr createRenderer(void) =0;
        virtual InputManager_sptr createInputManager(void);
        virtual ResourceManager_sptr createResourceManager(void);

        virtual void deleteTaskManager(void);
        virtual void deleteEventManager(void);
        virtual void deleteRenderer(void);
        virtual void deleteInputManager(void);
        virtual void deleteResourceManager(void);

	private:
		void shutdown(void);
        void registerListeners(void);
        bool onShutdown(Event_sptr e);
        bool onRequestQuit(Event_sptr e);
	};
}

#endif
