#include "tasks/TaskManager.h"

namespace pdEngine
{
	TaskManager::TaskManager() 
	{}
	
	TaskManager::~TaskManager() {}

    bool TaskManager::initAll()
    {
        for (auto t : taskList)
        {
            t->onInit();
            if (t->state == TaskState::uninitialized)
            {
                t->state = TaskState::running;
            }
            else {
                return false;
            }
        }
        return true;
    }

    void TaskManager::abortAllNow()
    {
        for (auto t : taskList)
        {
            if (t->isAlive()) 
            {
                t->onAbort();
                t->state = TaskState::aborted;
            }
        }
    }

	
	void TaskManager::updateTasks(TimeDelta timeDelta)
	{
        for (auto t : taskList)
        {
            switch (t->state)
            {
                case TaskState::running:
                    t->onUpdate(timeDelta);
                    break;
                case TaskState::ready:
                    t->state = TaskState::running;
                    break;
                case TaskState::paused:
                    break;
                case TaskState::succeeded:
                    t->onSuccess();
                    break;
                case TaskState::failed:
                    t->onFail();
                    t->state = TaskState::removed;
                    taskList.remove(t);
                    break;
                case TaskState::aborted:
                    t->onAbort();
                    t->state = TaskState::removed;
                    taskList.remove(t);
                    break;
                case TaskState::uninitialized:
                    t->onInit();
                    break;
                case TaskState::removed:
                    assert(false && "TaskManager should never see removed tasks");
                    break;
            }
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


    bool TaskManager::areAnyDead() 
    {
        for (auto t : taskList)
        {
            if (t->isDead()) {
                return true;
            }
        }
        return false;
    }

    int TaskManager::taskCount()
    {
        return taskList.size();
    }
}
