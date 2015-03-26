/*
 * TaskManager.h
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#ifndef PDENGINE_TASKMANAGER_H_
#define PDENGINE_TASKMANAGER_H_

#include "Task.h"
#include "Timer.h"

#include <memory>
#include <vector>

namespace pdEngine
{
    class TaskManager;
    using TaskManager_sptr = std::shared_ptr<TaskManager>;

	class TaskManager
	{
		std::vector<Task_sptr> taskList;

	public:
		TaskManager();
		~TaskManager();

        void init();

		void addTask(Task_sptr);

		void updateTasks(TimeDelta);
		void pauseTasks();
		void unPauseTasks();
		
	private:
        TimeDelta previous;
        bool paused;
	};
}

#endif /* PDENGINE_TASKMANAGER_H_ */
