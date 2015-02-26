#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "IGraphics.h"
#include <memory>

namespace pdEngine
{
	class Application
	{
	public:
		virtual Application();
		virtual ~Application();

		bool init();
		bool start();
	protected:
		virtual bool v_initTaskManager();
		virtual bool v_initEventManager();
		virtual bool v_initGraphics();
		virtual bool v_initGUI();

		virtual bool v_startTaskManager();
		virtual bool v_startEventManager();
		virtual bool v_startGraphics();
		virtual bool v_startGUI();
	private:
		std::unique_ptr<TaskManager> TaskManager;
	};
}


#endif
