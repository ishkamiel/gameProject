/*
 * TaskManager.h
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#ifndef PDENGINE_TASKMANAGER_H_
#define PDENGINE_TASKMANAGER_H_

#include "General.h"
#include "Task.h"

#include <vector>

namespace pdEngine
{
	class TaskManager
	{
	public:
		TaskManager();
		~TaskManager();

		void addTask(TaskSharedPtr);

		void updateTasks(TimeDelta);
		void pauseTasks();
		void unPauseTasks();
		
	private:
		std::vector<TaskSharedPtr> taskList;
	};
}

#endif /* PDENGINE_TASKMANAGER_H_ */
