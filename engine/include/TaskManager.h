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
        std::vector<Task_sptr>      taskList;
        TimeDelta                   previous;
        bool                        paused;
        bool                        removals;

    public:
        TaskManager();
        ~TaskManager();

        void initAll();

        void abortAllNow();

        void addTask(Task_sptr);

        void updateTasks(TimeDelta);
        void pauseTasks();
        void unPauseTasks();

        bool areAnyDead();

    private:
    };
}

#endif /* PDENGINE_TASKMANAGER_H_ */
