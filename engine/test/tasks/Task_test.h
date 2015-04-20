#ifndef TASK_TEST_H_
#define TASK_TEST_H_

#include "tasks/Task.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace  pdEngine
{
	class TaskManager
	{
	public:

		void onInit(Task_sptr t) { t->onInit(); }
		void onUpdate(Task_sptr t, TimeDelta td) { t->onUpdate(td); }
		void onSuccess(Task_sptr t) { t->onSuccess(); }
		void onFail(Task_sptr t) { t->onFail(); }
		void onAbort(Task_sptr t) { t->onAbort(); }
		void setState(Task_sptr t, pdEngine::TaskState state) { t->state = state; }
	};
	
	class SimpleTask : public Task
	{
	public:
		SimpleTask() {};
		virtual ~SimpleTask() {};
		std::string v_getTaskName(void) const noexcept override { return "Test Task"; }
		virtual void onUpdate(int t) noexcept override { (void)t; }
	};
}

namespace pdEngineTest
{
	
	
	class Task_test : public ::testing::Test
	{
	protected:
		std::shared_ptr<pdEngine::Task> t;
		std::shared_ptr<pdEngine::Task> t2;
		std::shared_ptr<pdEngine::Task> t3;
		std::shared_ptr<pdEngine::Task> t4;
		
		pdEngine::TaskManager* tm = nullptr;
		
		Task_test() {};
		
		virtual ~Task_test() {};
		
		virtual void SetUp();
		virtual void TearDown();
	};
}

#endif /* TASK_TEST_H_ */
