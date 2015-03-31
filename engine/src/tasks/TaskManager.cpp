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
            if (t->isUninitialized())
            {
                t->onInit();
                if (t->state == TaskState::uninitialized)
                {
                    t->state = TaskState::ready;
                }
                else {
                    return false;
                }
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
        auto i = taskList.begin();
        while (i != taskList.end())
        {
            switch ((*i)->state)
            {
                case TaskState::running:
                    (*i)->onUpdate(timeDelta);
                    ++i; break;
                case TaskState::ready:
                    (*i)->state = TaskState::running;
                    ++i; break;
                case TaskState::paused:
                    ++i; break;
                case TaskState::succeeded:
                    (*i)->onSuccess();
                    (*i)->state = TaskState::removed;
                    taskList.remove(*i++);
                    break;
                case TaskState::failed:
                    (*i)->onFail();
                    (*i)->state = TaskState::removed;
                    taskList.remove(*i++);
                    break;
                case TaskState::aborted:
                    (*i)->onAbort();
                    (*i)->state = TaskState::removed;
                    taskList.remove(*i++);
                    break;
                case TaskState::uninitialized:
                    (*i)->onInit();
                    if ((*i)->state == TaskState::uninitialized)
                        (*i)->state = TaskState::ready;
                    ++i; break;
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
