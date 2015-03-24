#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "EventManager.h"
#include "IGraphics.h"
#include "TaskManager.h"

#include "pdLogger.h"

#include <memory>

namespace pdEngine
{
    class ApplicationImpl;

    using App_sptr = std::shared_ptr<ApplicationImpl>;

	class Application
	{
		std::unique_ptr<TaskManager>    taskManager;
        EventManager_sptr               eventManager;
        Graphics_sptr                   graphicsEngine;
        App_sptr                        appimpl;

	public:
		Application();
		virtual ~Application();

		bool init();
		bool start();
		void shutdown();

    protected:
        virtual bool initGraphics();

	private:
	};
}


#endif
