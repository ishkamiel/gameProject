#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "EventManager.h"
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

	public:
		Application();
		virtual ~Application();

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
