#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Event.h"
#include "EventManager.h"
#include "InputManager.h"
#include "TaskManager.h"

#include <memory>

namespace pdEngine
{
    class ApplicationImpl;

	class Application
	{
        using ApplicatioImpl_sptr = std::shared_ptr<ApplicationImpl>;

		std::unique_ptr<TaskManager>    taskManager;
        EventManager_sptr               eventManager;
        ApplicatioImpl_sptr             pimpl;
        InputManager_sptr               inputManager;

        bool doShutdown { false };

	public:
		Application();
		virtual ~Application();

        virtual InputManager_sptr getInputManager();

        void addSubsystem(Task_sptr);

		bool init();
		bool start();
		void shutdown();

        bool onShutdown(Event_sptr e);
        bool onRequestQuit(Event_sptr e);

    protected:
        virtual bool initGraphics();

	private:
        bool setupTaskManager();
        bool setupApplicationImpl();
        bool setupEventManager();
	};
}

#endif
