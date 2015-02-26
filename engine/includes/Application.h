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
		
	private:
		pdUtils::LoggerSharedPtr log;
		std::unique_ptr<TaskManager> taskManager;
	};
}


#endif
