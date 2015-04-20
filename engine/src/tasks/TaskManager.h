#pragma once

#include "events/EventManagerImpl.h"
#include "tasks/Task.h"
#include "Timer.h"

#include <list>
#include <memory>

namespace pdEngine {

class TaskManager {
    std::list<Task_sptr> taskList;
    TimeDelta previous = 0;
    bool paused = false;

public:
    TaskManager(void);
    ~TaskManager(void);

    bool initAll(void);

    void abortAllNow(void);

    void addTask(Task_sptr);

    void updateTasks(int deltaMs);
    void pauseTasks(void);
    void unPauseTasks(void);

    unsigned int taskCount(void) const noexcept;
    bool areAnyDead(void);

private:
};

using TaskManager_sptr = std::shared_ptr<TaskManager>;
}
