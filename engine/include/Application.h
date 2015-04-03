#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "tasks/TaskManager.h"
#include "tasks/Task.h"
#include "renderer/Renderer.h"	

#include <memory>
#include <list>

namespace pdEngine
{
	class Application
	{
        TimerFrequency                  updateFrequency {240};

        std::shared_ptr<Renderer>		renderer;
        std::shared_ptr<Task>			inputManager;  
		std::shared_ptr<TaskManager>	taskManager;

        bool initOk                     { false };
        bool doShutdown                 { false };

	public:
		Application();
		virtual ~Application();

		bool init(void);
		bool start(void);

    protected:
        virtual void initLogging(void);

        virtual std::shared_ptr<Task> createInputManager(void);
        virtual std::shared_ptr<Renderer> createRenderer(void);
		//virtual std::list<Task> createTasks(void);

        virtual void deleteInputManager(void);
        virtual void deleteRenderer(void);
		//virtual void deleteTasks(void);

	private:
        void registerListeners(void);
		void shutdown(void);
        bool onShutdown(Event_sptr e);
        bool onRequestQuit(Event_sptr e);
	};
}

#endif
