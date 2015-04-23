#include "tasks/TaskManager.h"
#include "Logger.h"

namespace pdEngine
{

TaskManager::TaskManager(void)
{}

TaskManager::~TaskManager(void) {}

bool TaskManager::initAll(void)
{
    for (auto t : taskList)
    {
        if (t->isUninitialized())
        {
            t->onInit();
            if (t->state != TaskState::ready)
            {
                // TODO:  PDE_ERROR << "Failed to initialize " << t->v_getTaskName();
                return false;
            }
        }
    }
    return true;
}

void TaskManager::abortAllNow(void)
{
    for (auto t : taskList)
    {
        if (t->isAlive())
        {
            t->state = TaskState::aborted;
        }
    }
}


void TaskManager::updateTasks(int deltaMs)
{
    auto i = taskList.begin();
    while (i != taskList.end())
    {
        switch ((*i)->state)
        {
            case TaskState::running:
                (*i)->onUpdate(deltaMs);
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
                assert((*i)->state != TaskState::uninitialized);
                ++i; break;
            case TaskState::removed:
                assert(false);// "TaskManager should never see removed tasks");
                break;
        }
    }
}

void TaskManager::pauseTasks(void)
{
    for (auto t : taskList)
    {
        t->pause();
    }
}

void TaskManager::unPauseTasks(void)
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


bool TaskManager::areAnyDead(void) {
    for (auto t : taskList) {
        if (t->isDead()) {
            return true;
        }
    }
    return false;
}

unsigned int TaskManager::taskCount() const noexcept
{
    assert(INTMAX_MAX > taskList.size());
    return static_cast<unsigned int>(taskList.size());
}

}
