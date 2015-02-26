#include "TaskManager.h"

namespace pdEngine
{
	/*
	class TaskManager
	{
	public:
		TaskManager();
		~TaskManager();

		void addTask(TaskSharedPtr);

		void updateTasks(TimeDelta);
		void pauseTasks() {};
		void unPauseTasks() {};
	};
	*/
	
	TaskManager::TaskManager() 
	: taskList()
	{}
	
	TaskManager::~TaskManager() {}
	
	void TaskManager::updateTasks(TimeDelta timeDelta)
	{}
	
	void TaskManager::pauseTasks()
	{}
	
	void TaskManager::addTask(TaskSharedPtr newTask)
	{
		taskList.push_back(newTask);
	}
}