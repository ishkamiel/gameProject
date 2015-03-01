#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "EventManager.h"
#include "IGraphics.h"
#include "TaskManager.h"

#include "pdLogger.h"

#include <memory>

namespace pdEngine
{
	class Application
	{
		pdUtils::LoggerSharedPtr        log;
		std::unique_ptr<TaskManager>    taskManager;
        EventManager_sptr               eventManager;
        Graphics_sptr                   graphicsEngine;

	public:
		Application();
		virtual ~Application();

		bool init();
		bool start();

    protected:
        virtual bool initGraphics();

	private:
	};
}


#endif
