#include "TaskManager.h"

namespace pdEngine
{
	TaskManager::TaskManager() 
	{}
	
	TaskManager::~TaskManager() {}

    void TaskManager::init()
    {
        for (auto t : taskList)
        {
            t->onInit();
        }
    }

    bool TaskManager::areAnyDead() {
        for (auto t : taskList)
        {
            if (t->isDead()) {
                return true;
            }
        }
        return false;
    }
	
	void TaskManager::updateTasks(TimeDelta timeDelta)
	{
        for (auto t : taskList)
        {
            t->onUpdate(timeDelta);
        }
    }
	
	void TaskManager::pauseTasks()
	{
        for (auto t : taskList)
        {
            t->pause();
        }
    }

	void TaskManager::unPauseTasks()
	{
        for (auto t : taskList)
        {
            t->unPause();
        }
    }
	
	void TaskManager::addTask(Task_sptr newTask)
	{
		taskList.push_back(newTask);
	}
}
