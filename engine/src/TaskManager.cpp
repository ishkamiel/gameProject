#include "TaskManager.h"

namespace pdEngine
{
	TaskManager::TaskManager() 
	{}
	
	TaskManager::~TaskManager() {}

    void TaskManager::initAll()
    {
        for (auto t : taskList)
        {
            t->onInit();
            if (t->state == TaskState::uninitialized)
                t->state = TaskState::running;
            // if ( t->state == TaskState::uninitialized)
            //     throw std::logic_error("TaskState uninitialized after call to onInit");
        }
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
	
	void TaskManager::updateTasks(TimeDelta timeDelta)
	{
        for (auto t : taskList)
        {
            switch (t->state)
            {
                case TaskState::running:
                    t->onUpdate(timeDelta);
                    break;
                case TaskState::paused:
                    break;
                case TaskState::succeeded:
                    t->onSuccess();
                    break;
                case TaskState::failed:
                    t->onFail();
                    t->state = TaskState::removed;
                    removals = true;
                    break;
                case TaskState::aborted:
                    t->onAbort();
                    t->state = TaskState::removed;
                    removals = true;
                    break;
                case TaskState::uninitialized:
                    t->onInit();
                    break;
                case TaskState::removed:
                    assert(removals);
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
}
