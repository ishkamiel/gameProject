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

        TimerFrequency                  updateFrequency {120};

		TaskManager_sptr                taskManager;
        EventManager_sptr               eventManager;
        ApplicatioImpl_sptr             pimpl;
        InputManager_sptr               inputManager;

        bool doShutdown { false };

	public:
		Application();
		virtual ~Application();

        void addSubsystem(Task_sptr);

		bool init();
		bool start();
		void shutdown();

    protected:
        bool setupTaskManager();
        bool setupApplicationImpl();
        bool setupEventManager();
        bool setupInputManager();
	private:
        bool onShutdown(Event_sptr e);
        bool onRequestQuit(Event_sptr e);
	};
}

#endif
