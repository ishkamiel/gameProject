#ifndef APPLICATION_H_
#define APPLICATION_H_

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
        // Graphics_sptr                   graphicsEngine;
        ApplicatioImpl_sptr             pimpl;
        InputManager_sptr               inputManager;

	public:
		Application();
		virtual ~Application();

        virtual InputManager_sptr getInputManager();

        void addSubsystem(Task_sptr);

		bool init();
		bool start();
		void shutdown();

    protected:
        virtual bool initGraphics();

	private:
	};
}

#endif
