#include "stdafx.h"

#include "signalSlot/SignalManagerTest.h"

#include "engine/signalSlot/SignalManager.h"
#include "engine/signalSlot/SignalTask.h"

namespace
{

	struct TestEnvironment
	{
		bool isExpired = false;
		uint32_t nCalls = 0;
		void init() { isExpired = false; nCalls = 0; }
	};

	TestEnvironment testEnvironment;

	struct TestTask : engine::ISignalTask
	{


		bool isExpired() const override { return testEnvironment.isExpired; }

		void operator()() { testEnvironment.nCalls++; }

	};
}

namespace tests
{
	void SignalManagerTest::addTaskTest01()
	{
		testEnvironment.init();

		engine::SignalManager manager;
		std::unique_ptr<engine::ISignalTask> task(new TestTask());
		manager.addTask(std::move(task));
		manager.update();
		assertTrue(ASSERTION_PARAMETER(testEnvironment.nCalls == 1));
	}

	void SignalManagerTest::addTaskTest02()
	{
		testEnvironment.init();

		engine::SignalManager manager;
		std::unique_ptr<engine::ISignalTask> task(new TestTask());
		manager.addTask(std::move(task));
		manager.update();
		manager.update();
		assertTrue(ASSERTION_PARAMETER(testEnvironment.nCalls == 1));
	}

	void SignalManagerTest::addTaskTest03()
	{
		testEnvironment.init();

		engine::SignalManager manager;
		std::unique_ptr<engine::ISignalTask> task(new TestTask());
		std::unique_ptr<engine::ISignalTask> task2(new TestTask());
		manager.addTask(std::move(task));
		manager.addTask(std::move(task2));
		manager.update();
		assertTrue(ASSERTION_PARAMETER(testEnvironment.nCalls == 2));
	}

	void SignalManagerTest::expireTest01()
	{
		testEnvironment.init();

		engine::SignalManager manager;
		std::unique_ptr<engine::ISignalTask> task(new TestTask());
		manager.addTask(std::move(task));
		testEnvironment.isExpired = true;
		manager.update();
		assertTrue(ASSERTION_PARAMETER(testEnvironment.nCalls == 0));
	}
}
