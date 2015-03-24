/*
 * TaskManager.h
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#ifndef PDENGINE_TASKMANAGER_H_
#define PDENGINE_TASKMANAGER_H_

#include "Task.h"

#include <vector>

namespace pdEngine
{
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
	};
}

#endif /* PDENGINE_TASKMANAGER_H_ */
