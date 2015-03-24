#include "TaskManager.h"

namespace pdEngine
{
	TaskManager::TaskManager() 
	{}
	
	TaskManager::~TaskManager() {}

    void TaskManager::init()
    {
        //TODO
    }
	
	void TaskManager::updateTasks(TimeDelta timeDelta)
	{
        //TODO
        --timeDelta;
    }
	
	void TaskManager::pauseTasks()
	{
        //TODO
    }

	void TaskManager::unPauseTasks()
	{
        //TODO
    }
	
	void TaskManager::addTask(Task_sptr newTask)
	{
		taskList.push_back(newTask);
	}
}
