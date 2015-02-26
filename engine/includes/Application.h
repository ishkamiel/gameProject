#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "TaskManager.h"
#include "EventManager.h"
#include "pdLogger.h"

#include <memory>

namespace pdEngine
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		bool init();
		bool start();
	protected:
		virtual std::unique_ptr<TaskManager> v_getTaskManager();
		virtual std::unique_ptr<EventManager> v_getEventManager();
	private:
		std::unique_ptr<TaskManager> taskManager;
		pdUtils::LoggerSharedPtr log;
	};
}


#endif
