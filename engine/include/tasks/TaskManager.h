/*
 * TaskManager.h
 *
 *  Created on: Feb 26, 2015
 *      Author: ishkamiel
 */

#ifndef PDENGINE_TASKMANAGER_H_
#define PDENGINE_TASKMANAGER_H_

#include "events/EventManagerImpl.h"
#include "tasks/Task.h"
#include "Timer.h"

#include <list>
#include <memory>

namespace pdEngine {

class TaskManager {
    std::list<Task_sptr> taskList;
    TimeDelta previous;
    bool paused;

public:
    TaskManager(void);
    ~TaskManager(void);

    bool initAll(void);

    void abortAllNow(void);

    void addTask(Task_sptr);

    void updateTasks(TimeDelta);
    void pauseTasks(void);
    void unPauseTasks(void);

    int taskCount(void);
    bool areAnyDead(void);

private:
};

using TaskManager_sptr = std::shared_ptr<TaskManager>;
}
#endif /* PDENGINE_TASKMANAGER_H_ */
